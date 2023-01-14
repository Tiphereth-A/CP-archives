#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (int i = (l), i##end = (r); i <= i##end; ++i)
#define _rfor(i, r, l) for (int i = (r), i##end = (l); i >= i##end; --i)
const unsigned N = 1e6 + 1;
int h[N], v[N];
int L[N], R[N], V[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, n) cin >> h[i] >> v[i];
  {
    stack<int> s;
    _for(i, 1, n) {
      while (!s.empty() && h[s.top()] < h[i]) s.pop();
      L[i] = s.empty() ? 0 : s.top();
      s.push(i);
    }
  }
  {
    stack<int> s;
    _rfor(i, n, 1) {
      while (!s.empty() && h[s.top()] <= h[i]) s.pop();
      R[i] = s.empty() ? n + 1 : s.top();
      s.push(i);
    }
  }
  _for(i, 1, n) {
    V[L[i]] += v[i];
    V[R[i]] += v[i];
  }
  int ans = 0;
  _for(i, 1, n) ans = max(ans, V[i]);
  cout << ans;
}
