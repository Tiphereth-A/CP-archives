#include <bits/stdc++.h>
const int N = 1e5 + 5;
std::priority_queue<int> q;
int a[N], b[N], ans[N];
int n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i <= n; ++i) scanf("%d", b + i);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int tmp = a[i] + b[j];
      if (q.size() < n) q.push(tmp);
      else {
        if (q.top() > tmp) {
          q.pop();
          q.push(tmp);
        } else break;
      }
    }
  for (int i = n; i; --i) {
    ans[i] = q.top();
    q.pop();
  }
  for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
  return 0;
}
