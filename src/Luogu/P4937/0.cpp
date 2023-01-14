#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 100 + OFFSET, M = 2000 + OFFSET;
struct Node {
  int id, t, d, c;
  bool operator<(const Node &rhs) const { return d < rhs.d; }
} a[N];
int dp[M];
vi id[M];
int main() {
  int n;
  cin >> n;
  int max_d = -1;
  _for(i, 1, n) {
    cin >> a[i].t >> a[i].d >> a[i].c;
    a[i].id = i;
    chkmax(max_d, a[i].d);
  }
  sort(a + 1, a + n + 1);
  _for(i, 1, n)
    _rfor(j, a[i].d - 1, a[i].t)
      if (dp[j] < dp[j - a[i].t] + a[i].c) {
        (id[j] = id[j - a[i].t]).push_back(a[i].id);
        dp[j] = dp[j - a[i].t] + a[i].c;
      }
  int ans = -1;
  vi *ans_id;
  _for(i, 1, max_d)
    if (dp[i] > ans) {
      ans = dp[i];
      ans_id = &id[i];
    }
  cout << ans << endl << (*ans_id).size() << endl;
  for (int i : *ans_id) cout << i << " ";
  return 0;
}
