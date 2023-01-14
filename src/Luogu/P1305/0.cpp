#include <bits/stdc++.h>
struct tree {
  char val;
  int l, r;
} t[35];
int cnt;
int id[256];
int root[256];
void add(char fa, char lch, char rch) {
  int pos_fa = id[fa] ? id[fa] : (id[fa] = ++cnt);
  int pos_lch = lch == '*' ? 0 : (id[lch] ? id[lch] : (id[lch] = ++cnt));
  int pos_rch = rch == '*' ? 0 : (id[rch] ? id[rch] : (id[rch] = ++cnt));
  t[pos_fa] = {fa, pos_lch, pos_rch};
  t[pos_lch] = {lch, 0, 0};
  t[pos_rch] = {rch, 0, 0};
}
void f_i(int pos) {
  if (!pos) return;
  putchar(t[pos].val);
  f_i(t[pos].l);
  f_i(t[pos].r);
}
int main() {
  int n;
  std::cin >> n;
  char str[4];
  char &fa = str[0], &lch = str[1], &rch = str[2];
  for (int i = 1; i <= n; ++i) {
    std::cin >> str;
    add(fa, lch, rch);
    root[lch] = root[rch] = -1;
    if (~root[fa]) root[fa] = 1;
  }
  char r;
  for (int i = 0; i < 256; ++i) {
    if (root[i] == 1) {
      r = i;
      break;
    }
  }
  f_i(id[r]);
  return 0;
}
