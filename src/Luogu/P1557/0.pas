program main;

type
  bnum = array[0..250] of longint;
var
  a, c, x, cnt, ans1, ans2: bnum;
  s, s2: string;
  flag:  boolean;

  procedure print(a: bnum);
  var
    i: longint;
  begin
    if flag then
      Write('-');
    for i := a[0] downto 1 do
      Write(a[i]);
    writeln;
  end;

  procedure swap(var a: bnum; var b: bnum);
  begin
    c := a;
    a := b;
    b := c;
  end;

  procedure init(var a: bnum);
  begin
    fillchar(a, sizeof(a), 0);
    a[0] := 1;
  end;

  procedure solve(var a: bnum);
  var
    i: longint;
  begin
    for i := 1 to 3 do
    begin
      cnt[i + 1] := cnt[i + 1] + cnt[i] div 10;
      cnt[i] := cnt[i] mod 10;
    end;
    i := 3;
    while (cnt[i] = 0) do
      Dec(i);
    cnt[0] := i;
  end;

  procedure tobig(var a: bnum; s2: string);
  var
    i, len: longint;
  begin
    len  := length(s2);
    a[0] := len;
    for i := len downto 1 do
    begin
      a[len - i + 1] := Ord(s2[i]) - 48;
    end;
  end;

  procedure mul(var a: bnum; b: bnum);
  var
    i, j: longint;
  begin
    init(c);
    for i := 1 to a[0] do
      for j := 1 to b[0] do
        c[i + j - 1] := c[i + j - 1] + a[i] * b[j];
    for i := 1 to a[0] + b[0] - 1 do
    begin
      c[i + 1] := c[i + 1] + c[i] div 10;
      c[i] := c[i] mod 10;
    end;
    i := a[0] + b[0];
    while c[i] = 0 do
      Dec(i);
    c[0] := i;
    a := c;
  end;

  procedure sub(var a: bnum; b: bnum);
  var
    i: longint;
  begin
    flag := False;
    if a[0] < b[0] then
    begin
      swap(a, b);
      flag := True;
    end;
    if not flag then
      for i := a[0] downto 1 do
      begin
        if a[i] < b[i] then
        begin
          swap(a, b);
          flag := True;
          break;
        end
        else if a[i] > b[i] then
          break;
      end;
    for i := 1 to a[0] do
    begin
      a[i] := a[i] - b[i];
      if a[i] < 0 then
      begin
        a[i] := a[i] + 10;
        Dec(a[i + 1]);
      end;
    end;
    i := a[0];
    while (i > 0) and (a[i] = 0) do
      Dec(i);
    a[0] := i;
    if a[0] = 0 then
      Inc(a[0]);
  end;

  procedure add(var a: bnum; b: bnum);
  var
    i, len: longint;
  begin
    len := a[0];
    if b[0] > len then
      len := b[0];
    for i := 1 to len do
    begin
      a[i] := a[i] + b[i];
      a[i + 1] := a[i + 1] + a[i] div 10;
      a[i] := a[i] mod 10;
    end;
    i := len + 1;
    while (i > 0) and (a[i] = 0) do
      Dec(i);
    a[0] := i;
  end;

  procedure main;
  var
    i, n, bz: longint;
  begin
    readln(s);
    n := length(s);
    init(ans1);
    init(ans2);
    i  := 1;
    s2 := '';
    while (i <= n) and (s[i] in ['0'..'9']) do
    begin
      s2 := s2 + s[i];
      Inc(i);
    end;
    Dec(i);
    if s2 <> '' then
      tobig(ans1, s2);
    while (i < n) do
    begin
      Inc(i);
      if s[i] in ['+', '-'] then
      begin
        if s[i] = '+' then
          bz := 1
        else
          bz := 2;
        init(cnt);
        Inc(i);
        if s[i] = '(' then
        begin
          Inc(i);
          s2 := '';
          while (s[i] in ['0'..'9']) do
          begin
            s2 := s2 + s[i];
            Inc(i);
          end;
          tobig(cnt, s2);
        end
        else
        begin
          cnt[1] := 1;
          while s[i] in ['-', '+'] do
          begin
            Inc(cnt[1]);
            Inc(i);
          end;
          Dec(i);
          solve(cnt);
        end;
      end;
      init(x);
      Inc(i);
      s2 := '';
      while s[i] in ['0'..'9'] do
      begin
        s2 := s2 + s[i];
        Inc(i);
      end;
      Dec(i);
      tobig(x, s2);
      mul(x, cnt);
      if bz = 1 then
        add(ans1, x)
      else
        add(ans2, x);
    end;
    sub(ans1, ans2);
    print(ans1);
  end;

begin
  main;
end.
