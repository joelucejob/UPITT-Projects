package reversi_queue is

Capacity : constant integer := 64;
type Queue is private;

  QueueFull  : EXCEPTION;
  QueueEmpty : EXCEPTION;

  PROCEDURE QMakeEmpty (Q : IN OUT Queue);
  PROCEDURE Enqueue (Q : IN OUT Queue; R : in integer; C : in character);
  PROCEDURE Dequeue (Q : IN OUT Queue; R : out integer; C : out character);

private

  type row_array is array (1..Capacity) of integer;
  type col_array is array (1..Capacity) of character;
  type Queue IS RECORD
    Row : row_array;
    Col : col_array;
    Tail  : Natural := 0;
  END RECORD;

end reversi_queue;
