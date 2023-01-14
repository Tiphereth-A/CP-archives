#include <bits/stdc++.h>
using namespace std;
#include <atcoder/string.hpp>
using namespace atcoder;
int main() {
  string s;
  cin >> s;
  auto &&__ = lcp_array(s, suffix_array(s));
  cout << s.size() * (s.size() + 1) / 2 - accumulate(__.begin(), __.end(), 0ll);
  return 0;
}
