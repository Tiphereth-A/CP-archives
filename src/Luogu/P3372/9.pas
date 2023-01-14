program main;

var
  a: array[1..100005] of int64;
  sum, lazy: array[1..400005] of int64;
  n, m, i, b, x, y, z: int64;

  procedure pushup(rt: int64);
  begin
    sum[rt] := sum[rt shl 1] + sum[(rt shl 1) or 1];
  end;

  procedure build(l, r, rt: int64);
  var
    mid: int64;
  begin
    if l = r then
    begin
      sum[rt] := a[l];
      exit;
    end;
    mid := (l + r) shr 1;
    build(l, mid, rt shl 1);
    build(mid + 1, r, (rt shl 1) or 1);
    pushup(rt);
  end;

  procedure pushdown(rt, ln, rn: int64);
  begin
    if (lazy[rt] <> 0) then
    begin
      lazy[rt shl 1] := lazy[rt shl 1] + lazy[rt];
      lazy[(rt shl 1) or 1] := lazy[(rt shl 1) or 1] + lazy[rt];
      sum[rt shl 1] := sum[rt shl 1] + lazy[rt] * ln;
      sum[(rt shl 1) or 1] := sum[(rt shl 1) or 1] + lazy[rt] * rn;
      lazy[rt] := 0;
    end;
  end;

  procedure update(x, y, c, l, r, rt: int64);
  var
    mid: int64;
  begin
    if (x <= l) and (r <= y) then
    begin
      sum[rt]  := sum[rt] + c * (r - l + 1);
      lazy[rt] := lazy[rt] + c;
      exit;
    end;
    mid := (l + r) shr 1;
    pushdown(rt, mid - l + 1, r - mid);
    if x <= mid then
      update(x, y, c, l, mid, rt shl 1);
    if y > mid then
      update(x, y, c, mid + 1, r, (rt shl 1) or 1);
    pushup(rt);
  end;

  function query(x, y, l, r, rt: int64): int64;
  var
    mid, ans: int64;
  begin
    if (x <= l) and (r <= y) then
      exit(sum[rt]);
    ans := 0;
    mid := (l + r) shr 1;
    pushdown(rt, mid - l + 1, r - mid);
    if (x <= mid) then
      ans := ans + query(x, y, l, mid, rt shl 1);
    if (y > mid) then
      ans := ans + query(x, y, mid + 1, r, (rt shl 1) or 1);
    exit(ans);
  end;

begin
  readln(n, m);
  for i := 1 to n do
    Read(a[i]);
  build(1, n, 1);
  for i := 1 to m do
  begin
    Read(b);
    if b = 1 then
    begin
      readln(x, y, z);
      update(x, y, z, 1, n, 1);
    end
    else
    begin
      Read(x, y);
      writeln(query(x, y, 1, n, 1));
    end;
  end;
end.
