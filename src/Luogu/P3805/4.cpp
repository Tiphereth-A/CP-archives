#include <bits/stdc++.h>
using namespace std;
size_t manacher(std::string_view s) {
  std::string _ = "$#";
  _.reserve(2 * s.size() + 2);
  for (auto &&ch : s) {
    _.push_back(ch);
    _.push_back('#');
  }
  std::vector<size_t> r(_.size());
  size_t r_max = 0, mid = 0;
  for (size_t i = 1; i < _.size(); ++i) {
    r[i] = (i < r_max) ? std::min(r[(mid << 1) - i], r_max - i) : size_t(1);
    while (1 <= i - r[i] && i + r[i] <= _.size() && _[i - r[i]] == _[i + r[i]])
      ++r[i];
    if (i + r[i] > r_max) r_max = i + r[mid = i];
  }
  size_t l_max = 1;
  for (size_t i = 1; i < r.size(); ++i) l_max = std::max(l_max, r[i]);
  return l_max - 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  string s;
  cin >> s;
  cout << manacher(s);
  return 0;
}
