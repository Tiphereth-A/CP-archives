program main;

var
  i, n: longint;
  a: array[0..45] of longint;
begin
  a[0] := 1;
  a[1] := 1;
  readln(n);
  for i := 2 to n do
    a[i] := a[i - 2] + a[i - 1];
  writeln(a[n]);
end.
