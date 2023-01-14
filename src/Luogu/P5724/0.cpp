#include <bits/stdc++.h>
std::set<int> s;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1, _; i <= n; ++i) {
    scanf("%d", &_);
    s.insert(_);
  }
  printf("%d", *(s.rbegin()) - *(s.begin()));
}
