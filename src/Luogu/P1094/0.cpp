#include <bits/stdc++.h>
const int N = 30005;
int w, g, a[N];
int main() {
  scanf("%d%d", &w, &g);
  for (int i = 1; i <= g; ++i) scanf("%d", a + i);
  std::sort(a + 1, a + g + 1, std::greater<int>());
  int front = 1, rear = g, ans = 0;
  while (front < rear) {
    ++ans;
    if (a[front] + a[rear] <= w) {
      ++front;
      --rear;
    } else ++front;
  }
  printf("%d", (front == rear) ? ans + 1 : ans);
  return 0;
}
