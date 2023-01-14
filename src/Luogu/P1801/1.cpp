#include <bits/stdc++.h>
#define N 200005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
std::priority_queue<int, std::vector<int>, std::greater<int>> h_max;
std::priority_queue<int> h_min;
int n, m;
int a[N];
int main() {
  scanf("%d%d", &m, &n);
  _for(i, 1, m) scanf("%d", a + i);
  int top_of_h_max = 0, top_of_h_min = 0, tmp;
  for (int i = 1, j = 1; i <= n; ++i) {
    scanf("%d", &tmp);
    for (; j <= tmp; ++j) h_max.push(a[j]);
    h_min.push(h_max.top());
    h_max.pop();
    top_of_h_min = h_min.top();
    while (!h_max.empty() &&
           (top_of_h_max = h_max.top()) < (top_of_h_min = h_min.top())) {
      h_max.pop();
      h_min.pop();
      h_max.push(top_of_h_min);
      h_min.push(top_of_h_max);
    }
    printf("%d\n", top_of_h_min);
  }
  return 0;
}
