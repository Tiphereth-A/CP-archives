#include <bits/stdc++.h>
using namespace std;
string s;
bool check(string_view res) {
  string _;
  for (int i = 0; i < res.size(); ++i) {
    if (res[i] == 'H') _ += 'H';
    else _ += res;
    if (_.size() > 1000000) break;
  }
  return _ == s;
}
#define YES_         \
  {                  \
    cout << "Yes\n"; \
    return 0;        \
  }
#define NO_         \
  {                 \
    cout << "No\n"; \
    return 0;       \
  }
int main() {
  cin >> s;
  int q = count(s.begin(), s.end(), 'Q');
  if (q == 0) YES_;
  int sq = sqrt(q);
  if (sq * sq != q) NO_;
  int qi = s.find('Q');
  if (qi & 1) NO_;
  string res(qi / 2, 'H');
  for (int i = qi; i < s.size() && sq; ++i) {
    if (s[i] == 'Q') --sq;
    res += s[i];
  }
  qi = s.size() - s.find_last_of('Q') - 1;
  if (qi & 1) NO_;
  res += string(qi / 2, 'H');
  if (check(res)) YES_;
  NO_;
}
