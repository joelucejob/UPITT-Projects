with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;

package body reversi_stack is

--------------------------------------------------

    procedure StackInit (AStack: in out Stack) is
    begin
        AStack.Top := 0;
    end StackInit;

--------------------------------------------------

    procedure Push_Flips (AStack: in out Stack;
                    RItem : in RowItem;
                    CItem : in ColItem) is

        M : integer := AStack.Top;
        F : integer := AStack.Moves(M).Top2 + 1;

   begin -- Push
         if AStack.Top < StackMaximum then
            if AStack.Moves(M).Top2 < StackMaximum then
                AStack.Moves(M).Top2 := AStack.Moves(M).Top2 + 1;
                AStack.Moves(M).Row(F) := RItem;
                AStack.Moves(M).Col(F) := CItem;
            else
	        raise StackOverflow;
            end if;
         else
                raise StackOverflow;
         end if;
    end Push_Flips;

--------------------------------------------------

    procedure Push_Move (AStack: in out Stack) is
   
   begin -- Push
         if AStack.Top < StackMaximum then
             	AStack.Top := AStack.Top + 1;
         else
                put(item => "GG2");
             	raise StackOverflow;
         end if;
    end Push_Move;

--------------------------------------------------

    procedure Pop_Flips (AStack: in out Stack;
                   RItem : out RowItem;
                   CItem : out ColItem) is

        M : integer := AStack.Top;

    begin -- Pop
--                Put(item => AStack.Top);
  --              Put(item => AStack.Moves(M).Top2);
--		new_line;
--		Put(item => "HAHA");
         if AStack.Top > 0 then
	    if AStack.Moves(M).Top2 > 0 then
            	RItem := AStack.Moves(M).Row(AStack.Moves(M).Top2);
           	CItem := AStack.Moves(M).Col(AStack.Moves(M).Top2);
	--	put(Item => RItem);
	--	put(item => CItem);
	--	new_line;
             	AStack.Moves(M).Top2 := AStack.Moves(M).Top2 - 1;
	    end if;
         end if;
    end Pop_Flips;


--------------------------------------------------

    procedure Pop_Move (AStack: in out Stack) is

        M : integer := AStack.Top;

    begin -- Pop
         if AStack.Top > 0 then
                AStack.Top := AStack.Top - 1;
         end if;
    end Pop_Move;

--------------------------------------------------

    procedure SMakeEmpty (AStack : in out Stack) is
    begin
        AStack.Top := 0;
    end SMakeEmpty;

--------------------------------------------------

    function check_empty (AStack : in Stack) return boolean is
    begin
	if AStack.Top > 0 then
		if AStack.Moves(AStack.Top).Top2 > 1 then
			return false;
		end if;
	end if;
	return true;
    end check_empty;

--------------------------------------------------

        function GiveTurn(AStack : in Stack) return integer is
	begin 
		return AStack.Top;
	end GiveTurn;

--------------------------------------------------

    procedure GiveInfo (AStack : in Stack; R : out RowItem; C : out ColItem;
    			T : in integer) is
    begin
	if AStack.Top > 0 then
		R := AStack.Moves(T).Row(1);
		C := AStack.Moves(T).Col(1);
	end if;
    end GiveInfo;


end reversi_stack;
