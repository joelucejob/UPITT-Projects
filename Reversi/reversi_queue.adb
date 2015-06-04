package body reversi_queue is

--------------------------------------------------------

  PROCEDURE QMakeEmpty (Q : IN OUT queue) IS
  BEGIN
    Q.Tail := 0;
  END QMakeEmpty;

--------------------------------------------------------

  PROCEDURE Enqueue (Q : IN OUT Queue;
                     R : IN integer;
		     C : IN character) is

  BEGIN
    IF Q.Tail = Capacity THEN
      RAISE QueueFull;
    ELSE
      Q.Tail := Q.Tail + 1;
      Q.Row (Q.Tail) := R;
      Q.Col (Q.Tail) := C;
    END IF;
  END Enqueue;

----------------------------------------------------------

  PROCEDURE Dequeue (Q : IN OUT Queue;
                     R : out integer;
                     C : out character) is

  BEGIN
    IF Q.Tail = 0 THEN
      RAISE QueueEmpty;
    ELSE
      R := Q.Row(1);
      C := Q.Col(1);
      Q.Row (1..Q.Tail - 1) := Q.Row (2..Q.Tail); -- slice
      Q.Col (1..Q.Tail - 1) := Q.Col (2..Q.Tail); -- slice
      Q.Tail := Q.Tail -1;
    END IF;
  END Dequeue;

----------------------------------------------------------

end reversi_queue;
