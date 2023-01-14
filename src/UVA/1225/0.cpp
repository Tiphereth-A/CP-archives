#include <cstdio>
#include <string>
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    std::string s;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) s += std::to_string(i);
    int ans[10] = {};
    for (char ch : s) ++ans[ch - '0'];
    for (int i = 0; i < 10; ++i) printf("%d%c", ans[i], i == 9 ? '\n' : ' ');
  }
  return 0;
}
