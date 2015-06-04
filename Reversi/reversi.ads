with reversi_stack; use reversi_stack;
with reversi_queue; use reversi_queue; 

package reversi is

	type Board_Type is private;
	subtype Col_Type is character;
	subtype Row_Type is integer;

	Wrong_Input : exception;
	Surrender : exception;

	Procedure Intialize_Board (B : out Board_Type; 
				   S : out Stack;
				   Q : out Queue);
	Procedure Ask_Move(B : in out Board_Type; 
			S : in out Stack);
private

        Capacity : natural := 8;
        type Board_Type is array (1..Capacity, 1..Capacity) of integer;
	Turn : natural := 1;

end reversi;
