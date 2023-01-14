#include <bits/stdc++.h>
using namespace std;
int manacher(string_view a) {
  string s = "$#";
  for (auto &&ch : a) {
    s.push_back(ch);
    s.push_back('#');
  }
  vector<int> r(s.size());
  int r_max = 0, mid = 0;
  for (int i = 1; i < s.size(); ++i) {
    r[i] = (i < r_max) ? std::min(r[(mid << 1) - i], r_max - i) : int(1);
    while (1 <= i - r[i] && i + r[i] <= s.size() && s[i - r[i]] == s[i + r[i]])
      ++r[i];
    if (i + r[i] > r_max) {
      r_max = i + r[i];
      mid = i;
    }
  }
  int l_max = 0;
  for (int i = 1; i < r.size(); ++i) l_max = std::max(l_max, r[i] - 1);
  return l_max;
}
int main() {
  string s;
  cin >> s;
  cout << manacher(s);
}
