#include <ext/rope>
#include <iostream>
#include <string>
using namespace std;
using namespace __gnu_cxx;
const int N = 5e4 + 5;
crope now, s[N];
int cnt, d;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  int op, p, v, c;
  string str;
  while (kase--) {
    cin >> op;
    if (op == 1) {
      cin >> p >> str;
      now.insert(p - d, str.c_str());
      s[++cnt] = now;
    } else if (op == 2) {
      cin >> p >> c;
      now.erase(p - d - 1, c - d);
      s[++cnt] = now;
    } else {
      cin >> v >> p >> c;
      crope ans = s[v - d].substr(p - d - 1, c - d);
      d += count(ans.begin(), ans.end(), 'c');
      cout << ans << endl;
    }
  }
}
