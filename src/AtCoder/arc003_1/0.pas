program main;

var
  s: string;
  l, m, i: longint;
  x: double;
begin
  readln(l);
  Read(s);
  for i := 1 to l do
    case s[i] of
      'A': m := m + 4;
      'B': m := m + 3;
      'C': m := m + 2;
      'D': m := m + 1;
    end;
  x := m / l;
  writeln(x: 0: 15);
  readln;
  readln;
end.
