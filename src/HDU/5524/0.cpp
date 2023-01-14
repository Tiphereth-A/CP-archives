#include <cstdio>
#include <set>
std::set<i64> subtrees;
void dfs(i64 n) {
  if (n < 2) return;
  subtrees.insert(n);
  if (n == 2) return;
  int dep;
  i64 inf, sup;
  for (dep = 1; dep < 64; ++dep) {
    inf = (1ull << dep) - 1, sup = (1ull << (dep + 1)) - 1;
    if (n > inf && n < sup) break;
    subtrees.insert(inf);
    if (n == inf) return;
  }
  i64 leaves = inf + 1;
  if (n - leaves >= leaves / 2) {
    subtrees.insert(inf);
    dfs(n - inf - 1);
  } else dfs(n - inf / 2 - 1);
}
int main() {
  i64 n;
  while (~scanf("%llu", &n)) {
    subtrees.clear();
    subtrees.insert(n);
    if (n) subtrees.insert(1);
    dfs(n);
    printf("%llu\n", subtrees.size());
  }
}
