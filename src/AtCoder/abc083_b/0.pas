program main;

var
  a, b, c, i, j, z: longint;
  s: array[1..10000] of string;
  k: array[1..10000] of longint;
  ans: qword;
begin
  Read(a, b, c);
  for i := 1 to a do
  begin
    str(i, s[i]);
    for j := 1 to length(s[i]) do
    begin
      val(s[i][j], z);
      k[i] := k[i] + z;
    end;
    if (k[i] >= b) and (k[i] <= c) then
      Inc(ans, i);
  end;
  writeln(ans);
end.
