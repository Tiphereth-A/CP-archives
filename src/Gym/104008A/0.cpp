#include <bits/stdc++.h>
using namespace std;
void solve(int t_ = 0) {
  string s;
  cin >> s >> s;
  for (auto &ch : s) ch = (ch == '.' ? 'C' : ch);
  for (size_t i = 0; i < s.size(); ++i)
    if (s[i] == 'L') {
      if (i - 1 >= 0 && s[i - 1] == 'C') s[i - 1] = '.';
      if (i + 1 < s.size() && s[i + 1] == 'C') s[i + 1] = '.';
    }
  cout << s << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
