program main;

var
  a: array[1..100005] of int64;
  tree, tag: array[1..400005] of int64;
  n, m, i, x, y, op, k: int64;

  procedure pushup(p: int64);
  begin
    tree[p] := tree[p shl 1] + tree[(p shl 1) or 1];
  end;

  procedure init(p, l, r: int64);
  var
    mid: int64;
  begin
    if (l = r) then
    begin
      tree[p] := a[l];
      exit;
    end;
    mid := (l + r) shr 1;
    init(p shl 1, l, mid);
    init((p shl 1) or 1, mid + 1, r);
    pushup(p);
  end;

  procedure pushdown(p, ln, rn: int64);
  begin
    if (tag[p] <> 0) then
    begin
      tag[p shl 1] := tag[p shl 1] + tag[p];
      tag[(p shl 1) or 1] := tag[(p shl 1) or 1] + tag[p];
      tree[p shl 1] := tree[p shl 1] + tag[p] * ln;
      tree[(p shl 1) or 1] := tree[(p shl 1) or 1] + tag[p] * rn;
      tag[p] := 0;
    end;
  end;

  procedure update(p, l, r, ul, ur, k: int64);
  var
    mid: int64;
  begin
    if ((ul <= l) and (r <= ur)) then
    begin
      tree[p] := tree[p] + k * (r - l + 1);
      tag[p]  := tag[p] + k;
      exit;
    end;
    mid := (l + r) shr 1;
    pushdown(p, mid - l + 1, r - mid);
    if (ul <= mid) then
      update(p shl 1, l, mid, ul, ur, k);
    if (mid < ur) then
      update((p shl 1) or 1, mid + 1, r, ul, ur, k);
    pushup(p);
  end;

  function query(p, l, r, ul, ur: int64): int64;
  var
    ans, mid: int64;
  begin
    if ((ul <= l) and (r <= ur)) then
      exit(tree[p]);
    ans := 0;
    mid := (l + r) shr 1;
    pushdown(p, mid - l + 1, r - mid);
    if (ul <= mid) then
      ans := ans + query(p shl 1, l, mid, ul, ur);
    if (mid < ur) then
      ans := ans + query((p shl 1) or 1, mid + 1, r, ul, ur);
    exit(ans);
  end;

begin
  Read(n, m);
  for i := 1 to n do
    Read(a[i]);
  init(1, 1, n);
  for i := 1 to m do
  begin
    Read(op, x, y);
    if (op = 1) then
    begin
      Read(k);
      update(1, 1, n, x, y, k);
    end else
      writeln(query(1, 1, n, x, y));
  end;
end.
