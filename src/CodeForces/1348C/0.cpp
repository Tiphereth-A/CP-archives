#include <bits/stdc++.h>
using namespace std;
#define _all(a) (a).begin(), (a).end()
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, k;
    string str;
    cin >> n >> k >> str;
    sort(_all(str));
    if (str[0] != str[k - 1]) _run_continue(cout << str[k - 1] << '\n');
    if (str[k] != str.back())
      _run_continue(cout << str[0] << str.substr(k) << '\n');
    cout << str[0] << string((n - 1) / k, str[k]) << '\n';
  }
  return 0;
}
