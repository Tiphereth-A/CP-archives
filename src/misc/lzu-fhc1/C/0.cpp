#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int OFFSET = 5;
const int N = 100 + OFFSET;
const pii d[8] = {
  {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int maps0[N][N], maps[N][N], maps2[N][N];
int n;
int cnt(int i, int j) {
  int ret = 0;
  for (const pii &p : d)
    ret += maps[(i + p.first + n - 1) % n + 1][(j + p.second + n - 1) % n + 1];
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int k;
    cin >> n >> k;
    _for(i, 1, n)
      _for(j, 1, n) cin >> maps[i][j];
    _for(i, 1, n)
      _for(j, 1, n) maps0[i][j] = maps[i][j];
    _for(t, 1, k, _) {
      _for(i, 1, n)
        _for(j, 1, n) {
          _ = cnt(i, j);
          maps2[i][j] = (maps[i][j] == 0 && _ == 3)           ? 1 :
                        (maps[i][j] == 1 && (_ > 3 || _ < 2)) ? 0 :
                                                                maps[i][j];
        }
      _for(i, 1, n)
        _for(j, 1, n) maps[i][j] = maps2[i][j];
      bool f = 1;
      _for(i, 1, n)
        _for(j, 1, n) f &= maps0[i][j] == maps[i][j];
      if (f) {
        cout << "YES\n" << t << '\n';
        return;
      }
    }
    cout << "NO\n";
  }
  return 0;
}
