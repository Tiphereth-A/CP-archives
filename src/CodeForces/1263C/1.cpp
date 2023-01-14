#include <bits/stdc++.h>
int _[100005];
int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    int cnt = 0;
    for (int l = 1; l <= n; l = n / (n / l) + 1) _[++cnt] = n / l;
    std::cout << cnt + 1 << std::endl << "0 ";
    for (int i = cnt; i; --i) std::cout << _[i] << " ";
    std::cout << std::endl;
  }
  return 0;
}
