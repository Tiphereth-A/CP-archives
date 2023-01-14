#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::string;
void solve(string m, string l) {
  int root_pos_l = l.size() - 1;
  int root_pos_m = m.find(l[root_pos_l]);
  cout << l[root_pos_l];
  int lch_len = root_pos_m, rch_len = m.size() - root_pos_m - 1;
  if (lch_len) solve(m.substr(0, lch_len), l.substr(0, lch_len));
  if (rch_len)
    solve(m.substr(root_pos_m + 1, rch_len), l.substr(lch_len, rch_len));
}
int main() {
  string m, l;
  cin >> m >> l;
  solve(m, l);
  return 0;
}
