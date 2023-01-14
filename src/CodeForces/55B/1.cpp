#include <bits/stdc++.h>
char op[3];
const int frac[] = {1, 1, 2, 6, 24};
long long dfs(int tot, long long *__num) {
  if (tot == 1) return *__num;
  long long num[tot], _ = 0x3f3f3f3f3f3f3f3fll;
  int id[tot], __ = frac[tot];
  for (int i = 0; i < tot; ++i) id[i] = i;
  do {
    for (int i = 0; i < tot; ++i) num[i] = __num[id[i]];
    long long a = num[0], b = num[1];
    num[1] = (op[4 - tot] == '+') ? a + b : a * b;
    _ = std::min(_, dfs(tot - 1, num + 1));
    std::next_permutation(id, id + tot);
  } while (--__);
  return _;
}
int main() {
  long long __num[4];
  std::cin >> __num[0] >> __num[1] >> __num[2] >> __num[3];
  std::cin >> op[0] >> op[1] >> op[2];
  std::cout << dfs(4, __num);
  return 0;
}
