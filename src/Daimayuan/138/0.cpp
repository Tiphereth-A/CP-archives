#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, k;
  cin >> n >> k;
  if (k >= n) {
    cout << "0\n";
    return 0;
  };
  vector<int> c;
  c.reserve(n);
  _for(i, 1, n, x) {
    cin >> x;
    c.push_back(x);
  }
  sort(c.begin(), c.end());
  priority_queue<int> pq;
  _for(i, 1, n - 1)
    if (c[i] - c[i - 1] > 0) pq.push(c[i] - c[i - 1]);
  while (--k && !pq.empty()) pq.pop();
  i64 ans = 0;
  while (!pq.empty()) {
    ans += pq.top();
    pq.pop();
  }
  cout << ans;
  return 0;
}
