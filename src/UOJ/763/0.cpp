#include <bits/stdc++.h>
using u64 = uint64_t;
const int N = 60, M = 998244353;
const u64 mask = std::chrono::steady_clock::now().time_since_epoch().count();
u64 shift(u64 x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}
std::vector<int> edge[N];
u64 sub[N], root[N];
std::map<u64, int> trees;
void getSub(int x) {
  sub[x] = 1;
  for (int i : edge[x]) {
    getSub(i);
    sub[x] += shift(sub[i]);
  }
}
void getRoot(int x) {
  for (int i : edge[x]) {
    root[i] = sub[i] + shift(root[x] - shift(sub[i]));
    getRoot(i);
  }
}
int main() {
  int m;
  cin >> m;
  for (int t = 1; t <= m; t++) {
    int n, rt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      int fa;
      cin >> fa;
      if (fa) edge[fa].push_back(i);
      else rt = i;
    }
    getSub(rt);
    root[rt] = sub[rt];
    getRoot(rt);
    u64 hash = 1;
    for (int i = 1; i <= n; i++) { hash += shift(root[i]); }
    if (!trees.count(hash)) { trees[hash] = t; }
    cout << trees[hash];
    for (int i = 1; i <= n; i++) { edge[i].clear(); }
  }
}
