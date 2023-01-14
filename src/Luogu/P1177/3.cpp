#include <bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, a[MAXN], tmp[MAXN << 1];
int winner(int pos1, int pos2) {
  int u = pos1 >= n ? pos1 : tmp[pos1];
  int v = pos2 >= n ? pos2 : tmp[pos2];
  if (tmp[u] <= tmp[v]) return u;
  return v;
}
void creat_tree(int &value) {
  for (int i = 0; i < n; i++) tmp[n + i] = a[i];
  for (int i = 2 * n - 1; i > 1; i -= 2) {
    int k = i / 2;
    int j = i - 1;
    tmp[k] = winner(i, j);
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}
void recreat(int &value) {
  int i = tmp[1];
  while (i > 1) {
    int j, k = i / 2;
    if (i % 2 == 0) j = i + 1;
    else j = i - 1;
    tmp[k] = winner(i, j);
    i = k;
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}
void tournament_sort() {
  int value;
  creat_tree(value);
  for (int i = 0; i < n; i++) {
    a[i] = value;
    recreat(value);
  }
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  for (int i = 0; i < n; ++i) std::cin >> a[i];
  tournament_sort();
  for (int i = 0; i < n; ++i) std::cout << a[i] << " \n"[i + 1 == n];
  return 0;
}
