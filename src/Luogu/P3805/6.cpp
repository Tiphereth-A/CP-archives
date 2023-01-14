#include <bits/stdc++.h>
using namespace std;
int manacher(string_view a) {
  string s = "$#";
  for (char ch : a) {
    s.push_back(ch);
    s.push_back('#');
  }
  vector<size_t> r(s.size());
  size_t len = s.size() - 1;
  int r_max = 0, mid = 0;
  for (size_t i = 1; i <= len; ++i) {
    r[i] = (i < r_max) ? std::min(r[(mid << 1) - i], r_max - i) : size_t(1);
    while (1 <= i - r[i] && i + r[i] <= len && s[i - r[i]] == s[i + r[i]])
      ++r[i];
    if (i + r[i] > r_max) {
      r_max = i + r[i];
      mid = i;
    }
  }
  size_t l_max = 0;
  for (size_t i = 1; i <= len; ++i) l_max = max(l_max, r[i] - 1);
  return l_max;
}
int main() {
  string s;
  cin >> s;
  cout << manacher(s);
}
