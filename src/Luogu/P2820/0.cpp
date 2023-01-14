#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 1e4 + 5;
const int M = 1e4 + 5;
int n, k;
unsigned long long sum;
struct edge {
  int from, to, val;
  bool operator<(const edge &other) const { return val < other.val; }
} e[M];
int fa[N];
int find(int x) {
  return x == fa[x] ? x : fa[fa[fa[fa[x]]]] = find(fa[fa[fa[fa[x]]]]);
}
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= k; ++i) {
    cin >> e[i].from >> e[i].to >> e[i].val;
    sum += e[i].val;
  }
  std::sort(e + 1, e + k + 1);
  int cnt = 0;
  for (int i = 1; i <= k && cnt < n - 1; ++i) {
    int fx = find(e[i].from), fy = find(e[i].to);
    if (fx != fy) {
      sum -= e[i].val;
      fa[fx] = fy;
      ++cnt;
    }
  }
  cout << sum;
  return 0;
}
