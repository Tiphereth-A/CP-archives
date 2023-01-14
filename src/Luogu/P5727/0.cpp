#include <bits/stdc++.h>
std::stack<int> s;
int main() {
  int n;
  scanf("%d", &n);
  s.push(n);
  while (n != 1) s.push(n = n & 1 ? n * 3 + 1 : n / 2);
  while (!s.empty()) {
    printf("%d ", s.top());
    s.pop();
  }
}
