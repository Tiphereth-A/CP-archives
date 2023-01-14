#include <bits/stdc++.h>
#define N 200005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
std::priority_queue<int, std::vector<int>, std::greater<int>> h_max;
std::priority_queue<int> h_min;
int n, m;
int a[N];
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c - 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
int main() {
  read(m);
  read(n);
  _for(i, 1, m) read(a[i]);
  int top_of_h_max = 0, top_of_h_min = 0, tmp;
  for (int i = 1, j = 1; i <= n; ++i) {
    read(tmp);
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
