#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const int N = 1000 + 7;
int n, bucket[N], a[N], to[N];
string str, pre[N];
void Get(const string &s, string &res) {
  int cnt = 0;
  _for(i, 'a', 'z') bucket[i] = to[i] = a[i] = 0;
  n = s.size();
  _rfor(i, n - 1, 0)
    if (!bucket[s[i]]) {
      bucket[s[i]]++;
      a[s[i]] = cnt++;
    }
  _for(i, 'a', 'z') to[i] = 'a' + a[i];
  res = s;
  _for(i, 0, n) res[i] = to[s[i]];
}
int main() {
  cin >> n >> str;
  string _;
  _for(i, 0, n - 1) Get(_ += str[i], pre[i]);
  sort(pre, pre + n, greater<string>());
  cout << pre[0];
  return 0;
}
