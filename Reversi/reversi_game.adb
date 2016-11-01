with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;
with reversi; use reversi;
with reversi_stack; use reversi_stack;
with reversi_queue; use reversi_queue;

procedure reversi_game is

---------------------------------------------------
-- Author : Joseph Luce
-- This program recreates the game reversi
---------------------------------------------------

MENU_INPUT : integer;	-- user input for menu options
GAME_BOARD : Board_Type;
GAME_HISTORY : Stack;
HISTORY : Queue;

---------------------------------------------------

procedure menu (INPUT : out integer) is
	
begin -- menu
  loop
	INPUT := 0;
	put(item => "1: Play Game");
	new_line;
        put(item => "2: View History");
        new_line;
        put(item => "3: Quit");
        new_line;
	get(item => INPUT);
	if INPUT < 1 or INPUT > 3 then
		put(item => "Incorrect menu option.");
		new_line;
	end if;
	exit when INPUT > 0 or INPUT < 2;
  end loop;

end menu;

---------------------------------------------------

Row, T : integer;
Col : character;

begin -- reversi_game

loop

	menu(MENU_INPUT);
	exit when MENU_INPUT = 3;
	if MENU_INPUT = 1 then
		Intialize_Board (GAME_BOARD, GAME_HISTORY, HISTORY);
		Ask_Move(GAME_BOARD, GAME_HISTORY);
	elsif Menu_Input = 2 then
      		T := GiveTurn(GAME_HISTORY);
		if T > 0 then 
                	for i in 1..T loop
				GiveInfo(GAME_HISTORY, Row, Col, i);
				Enqueue(HISTORY, Row, Col);
                	end loop;
			for j in 1..T loop
                                Dequeue(HISTORY, Row, Col);
				put(item => j);
				put(item => ": ");
				put(item => Row);
				put(item => Col);
				new_line;
			end loop;
		end if;
	end if;

end loop;

end reversi_game;
