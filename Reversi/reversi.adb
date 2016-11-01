with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;
with reversi_stack; use reversi_stack;
with reversi_queue; use reversi_queue;

package body reversi is

---------------------------------------------------

Procedure Intialize_Board (B : out Board_Type;
			   S : out Stack;
			   Q : out Queue) is

temp_num : integer;

begin -- Intialize_Board
	-- Reset the entire board
	SMakeEmpty(S);
	QMakeEmpty(Q);
	Turn := 1;
	for i in 1..Capacity loop
		for j in 1..Capacity loop
			B(i,j) := 0;
		end loop;
	end loop;

	-- Set the starting pieces
	temp_num := (Capacity / 2);
	B(temp_num, temp_num) := 1;
        B(temp_num + 1, temp_num + 1) := 1;
        B(temp_num + 1, temp_num) := 2;
        B(temp_num, temp_num + 1) := 2;
end Intialize_Board;

---------------------------------------------------

Procedure Print_Board (B : in Board_Type) is

        Type Column_Type is array(1..10) of character;
        Column_Axis : Column_Type := "abcdefghij";

begin -- Print_Board

	-- Create top axis
        put (item => "  | ");
	for i in 1..Capacity loop
		put (item => Column_Axis(i));
		put (item => " | ");				
	end loop;
	new_line;	
        put (item => "  ");
        for l in 1..Capacity loop
        	put (item => "____");
	end loop;
	new_line;

        -- Create board
	--rows
	for i in 1..Capacity loop	
		-- columns
		put (item => i, width => 1);
        	put (item => " | ");
        	for j in 1..Capacity loop
		--empty
		if B(i,j) = 0 then
			put (item => " ");
		--white
		elsif B(i,j) = 1 then
	                       put (item => "W");
		--black
		else
			put (item => "B");
		end if;
                put (item => " | ");
                if j = Capacity then
                        put (item => i, width => 1);
                end if;
		end loop;

		new_line;
        	put (item => "  ");
		for l in 1..Capacity loop
			put (item => "____");
		end loop;
		new_line;
	end loop;

	-- Create bottom axis
        put (item => "  | ");
        for i in 1..Capacity loop
        	put (item => Column_Axis(i));
                put (item => " | ");
        end loop;
        new_line;

end Print_Board;

---------------------------------------------------

Function Char_To_Int (S : in Col_Type) return integer is

begin -- Char_To_Int

	if S = 'a' then
		return 1;
	elsif S = 'b' then
		return 2;
        elsif S = 'c' then
                return 3;
        elsif S = 'd' then
                return 4;
        elsif S = 'e' then
                return 5;
        elsif S = 'f' then
                return 6;
        elsif S = 'g' then
                return 7;
        elsif S = 'h' then
                return 8;
        end if;
	return -1;

end Char_To_Int;

---------------------------------------------------

Function Valid (B : in Board_Type;
                X, Y, dX, dY : in integer) return boolean is

tempx, tempy : integer;

begin -- valid

	tempx := X;
	tempy := Y;
        --check if illegal coordinate
        if Capacity >= X and
           X >= 1 and
           Capacity >= Y and
           Y >= 1 then
                --check is empty
                if B(X, Y) /= 0 then
			--nearby color is opposite
                        if Turn = 1 and B(X, Y) = 2 then
				tempx := tempx + dx;
				tempy := tempy + dy;
				--check if far color is same
				while tempx >= 1 and
				      Capacity >= tempx and
				      tempy >= 1 and
				      Capacity >= tempy loop
					if B(tempx, tempy) = 1 then
						return true;
					end if;
				        tempx := tempx + dx;
				        tempy := tempy + dy;
				end loop;
			elsif Turn = 2 and B(X, Y) = 1 then
                                tempx := tempx + dx;
                                tempy := tempy + dy;
                                while tempx >= 1 and
                                      Capacity >= tempx and
                                      tempy >= 1 and
                                      Capacity >= tempy loop
                                        if B(tempx, tempy) = 2 then
                                                return true;
                                        end if;
                                        tempx := tempx + dx;
                                        tempy := tempy + dy;
				end loop;
                        end if;
                end if;
        end if;
        return false;

end Valid;

---------------------------------------------------

Function Valid_Move (B : in Board_Type;
		     R : in Row_Type;
		     C : in integer) return boolean is

tempx, tempy : integer;
deltax, deltay : integer;

begin -- Valid_Move
        --check top left	
	deltax := -1;
	deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
	if Valid(B, tempx, tempy, deltax, deltay) = true then
		return true;
	end if;
	--check top
	deltax := 0;
        deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
		return true;
	end if;
        --check top right
        deltax := 1;
        deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
        --check right
        deltax := -1;
        deltay := 0;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
        --check left
        deltax := 1;
        deltay := 0;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
        --check bottom left
        deltax := -1;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
        --check bottom
        deltax := 0;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
        --check bottom right
        deltax := 1;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                return true;
        end if;
	return false;

end Valid_Move;

---------------------------------------------------

Function Int_To_Char (S : in RowItem) return character is

begin -- Int_To_Char

        if S = 1 then
                return 'a';
        elsif S = 2 then
                return 'b';
        elsif S = 3 then
                return 'c';
        elsif S = 4 then
                return 'd';
        elsif S = 5 then
                return 'e';
        elsif S = 6 then
                return 'f';
        elsif S = 7 then
                return 'g';
        elsif S = 8 then
                return 'h';
        end if;
        return 'a';

end Int_To_Char;

---------------------------------------------------

Procedure Flipper (B : in out Board_Type;
                   X, Y, dX, dY : in integer;
		   S : in out Stack) is

tempx, tempy : integer;

begin -- Flipper

	tempx := X;
	tempy := Y;
        --check if illegal coordinate
        if Capacity >= X and
           X >= 1 and
           Capacity >= Y and
           Y >= 1 then
                --check is empty
                if B(X, Y) /= 0 then
			--nearby color is opposite
                        if Turn = 1 and B(X, Y) = 2 then
				tempx := tempx + dx;
				tempy := tempy + dy;
				--if far color is opposite then flip
				while tempx >= 1 and
				      Capacity >= tempx and
				      tempy >= 1 and
				      Capacity >= tempy loop
					if B(tempx, tempy) = 1 then
						B(tempx - dx, tempy - dy) := 1;
						Push_Flips(S, tempx - dx, Int_To_Char(tempy - dy));
					end if;
				        tempx := tempx + dx;
				        tempy := tempy + dy;
				end loop;
			elsif Turn = 2 and B(X, Y) = 1 then
                                tempx := tempx + dx;
                                tempy := tempy + dy;
                                while tempx >= 1 and
                                      Capacity >= tempx and
                                      tempy >= 1 and
                                      Capacity >= tempy loop
                                        if B(tempx, tempy) = 2 then
                                                B(tempx - dx, tempy - dy) := 2;
                                                Push_Flips(S, tempx - dx, Int_To_Char(tempy - dy));
                                        end if;
                                        tempx := tempx + dx;
                                        tempy := tempy + dy;
				end loop;
                        end if;
                end if;
        end if;

end Flipper;

---------------------------------------------------

Procedure Flip (B : in out Board_Type;
		R : in Row_Type;
		C : in integer;
		S : in out Stack) is

tempx, tempy : integer;
deltax, deltay : integer;

begin -- Flip

        --flip top left	
	deltax := -1;
	deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
	if Valid(B, tempx, tempy, deltax, deltay) = true then
		Flipper(B, tempx, tempy, deltax, deltay, S);		
	end if;
	--flip top
	deltax := 0;
        deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
	end if;
        --flip top right
        deltax := 1;
        deltay := -1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;
        --flip right
        deltax := -1;
        deltay := 0;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;
        --flip left
        deltax := 1;
        deltay := 0;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;
        --flip bottom left
        deltax := -1;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;
        --flip bottom
        deltax := 0;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;
        --flip bottom right
        deltax := 1;
        deltay := 1;
        tempx := R + deltax;
        tempy := C + deltay;
        if Valid(B, tempx, tempy, deltax, deltay) = true then
                Flipper(B, tempx, tempy, deltax, deltay, S);
        end if;

end Flip;

---------------------------------------------------

Procedure Undo_Move (B : in out Board_Type; Sa : in out Stack) is

R : RowItem;
C : ColItem;

begin -- Undo_Move

	while check_empty(Sa) = false loop
		Pop_Flips(Sa, R, C);
		if Turn = 1 then
			B(R, Char_To_Int(C)) := 1;
		else 
                        B(R, Char_To_Int(C)) := 2;
		end if;
	end loop;
        Pop_Flips(Sa, R, C);
        B(R, Char_To_Int(C)) := 0;
	
	if Turn = 1 then
		Turn := 2;
	else 
		Turn := 1;
	end if;
        Pop_Move(Sa);

end Undo_Move;

---------------------------------------------------

Procedure Modify_Board (B : in out Board_Type;
                        R : in Row_Type;
                        C : in Col_Type;
			S : in out Stack) is

begin -- Modify_Board

        if Turn = 1 then
                B(R, Char_To_Int(C)) := 1;
                Flip (B, R, Char_To_Int(C), S);
        elsif Turn = 2 then
                B(R, Char_To_Int(C)) := 2;
                Flip (B, R, Char_To_Int(C), S);
        else
                raise Wrong_Input;
        end if;

        exception
                when Surrender =>
                        put (item => "Quit");
                when Wrong_Input =>
                        put (item => "Wrong Input");

end Modify_Board;

---------------------------------------------------

Procedure Count_Flips (B : in Board_Type; 
            	       Wh : out integer; 
	       	       Bl : out integer) is

White : integer := 0;
Black : integer := 0;

begin --Count_Flips

	for i in 1..Capacity loop
		for j in 1..Capacity loop
			if B(i,j) = 1 then
				White := White + 1;
			elsif B(i,j) = 2 then
				Black := Black + 1;
			end if;	
		end loop;
	end loop;
	Wh := White;
	Bl := Black;

end Count_Flips;


---------------------------------------------------

Function Check_Victory (B : in Board_Type) return boolean is 

V : boolean := false;
White : integer := 0;
Black : integer := 0;

begin -- Check_Victory

	--check if any valid moves on the board
	for i in 1..Capacity loop
		for j in 1..Capacity loop
			if V = false then
				V := Valid_Move(B, i, j);
			end if;			
		end loop;
	end loop;

	--if there are no valid moves left on the board
	if V = false then
		Count_Flips(B, White, Black);
		if White > Black then
			Put(item => "White is the winner!");
			new_line;
                elsif White = Black then
                        put(item => "Its a tie!");
                        new_line;
		else
			put(item => "Black is the winner!");
			new_line;
		end if;
		put(item => "White: ");
		put(item => White);
		new_line;
		put(item => "Black: ");
		put(item => Black);
		new_line;
	end if;
	return V;

end Check_Victory;

---------------------------------------------------

Procedure Ask_Move (B : in out Board_Type; S : in out Stack) is

INPUT, White, Black : integer := 0;
ROW : Row_Type;
COL : Col_Type;

begin -- Ask_Move

  loop
        new_line(spacing => 2);
        Print_Board(B);
	new_line(spacing => 2);
	if Turn = 1 then
		put (item => "White's Turn:");
		new_line;
	else
                put (item => "Black's Turn:");
                new_line;
	end if;
	put (item => "What would you like to do?");
	new_line;
	put (item => "1. Play a move.");
	new_line;
	put (item => "2. Undo last move.");
	new_line;
	put (item => "3. Quit.");
	new_line;
	get (item => INPUT);
	
	--Play a move
	if INPUT = 1 then
	   --check if no more moves are left
		if Check_Victory(B) = false then
			exit;
	   	end if;
                put (item => "Row(Integer):");
		get (item => ROW);
                put (item => "Column(Character):");
        	get (item => COL);
		new_line(spacing => 2);
		-- Check if position is taken
		if Valid_Move(B, ROW, Char_To_Int(COL)) = true then
			Push_Move(S);
			Push_Flips(S, ROW, COL); 
			Modify_Board(B, ROW, COL, S);
			-- Change player turn			
	                if Turn = 1 then
        	                Turn := 2;
                	else
                        	Turn := 1;
                	end if;
		else
                	put (item => "Not a valid move.");
			new_line;
		end if;
	end if;
	if INPUT = 2 then
		Undo_move(B, S);
	end if;
	if INPUT = 3 then
                Count_Flips(B, White, Black);
                if White > Black then
                        Put(item => "White is the winner!");
                        new_line;
		elsif White = Black then
			put(item => "Its a tie!");
			new_line;
                else
                        put(item => "Black is the winner!");
                        new_line;
                end if;
                put(item => "White: ");
                put(item => White);
                new_line;
                put(item => "Black: ");
                put(item => Black);
                new_line;
		exit;
	end if;
	new_line(spacing => 2);
  end loop;

end Ask_Move;

--------------------------------------------------

end reversi;
