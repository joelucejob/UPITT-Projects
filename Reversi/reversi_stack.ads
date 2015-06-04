package reversi_stack is

        StackMaximum: constant integer := 64;
	subtype RowItem is integer;
	subtype ColItem is character;
	type Stack is private;
	type Flips is private;

	StackUnderflow: EXCEPTION;
	StackOverflow: EXCEPTION;
	
	procedure Push_Flips (AStack: in out Stack;
			RItem : in RowItem;
			CItem : in ColItem);
	procedure Pop_Flips (AStack: in out Stack;
		       RItem : out RowItem;
		       CItem : out ColItem);
        procedure Push_Move (AStack: in out Stack);

        procedure Pop_Move (AStack: in out Stack);

	procedure SMakeEmpty (AStack : in out Stack);

 	function check_empty(AStack : in Stack) return boolean;

	function GiveTurn(AStack : in Stack) return integer; 

	procedure GiveInfo(AStack : in Stack;
			R : out RowItem;
			C : out ColItem;
			T : in integer);

private

        type row_array is array (1..StackMaximum) of RowItem;
        type col_array is array (1..StackMaximum) of ColItem;

	type Flips is record
		Row : row_array;
		Col : col_array;
		Top2 : integer range 0..StackMaximum := 0;
	end record;

        type Move_Array is array (1..StackMaximum) of Flips;

        type Stack is record
		Moves : Move_Array;
                Top: integer range 0..StackMaximum := 0;
        end record;

end reversi_stack;
