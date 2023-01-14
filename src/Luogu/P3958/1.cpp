#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node {
  int x, y, z;
};
ll dist(Node l, Node r) {
  return 1ll * (l.x - r.x) * (l.x - r.x) + 1ll * (l.y - r.y) * (l.y - r.y) +
         1ll * (l.z - r.z) * (l.z - r.z);
}
vector<int> fa;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, h, r;
    cin >> n >> h >> r;
    vector<Node> p(n);
    for (auto &i : p) cin >> i.x >> i.y >> i.z;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> u, d;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (dist(p[i], p[j]) <= 4ll * r * r) merge(i, j);
    for (int i = 0; i < n; i++)
      if (p[i].z <= r) d.push_back(i);
    for (int i = 0; i < n; i++)
      if (p[i].z + r >= h) u.push_back(i);
    bool f = 0;
    for (int i = 0; i < u.size(); i++) {
      if (f) break;
      for (int j = 0; j < d.size(); j++) {
        if (f) break;
        if (find(u[i]) == find(d[j])) {
          f = 1;
          cout << "Yes\n";
        }
      }
    }
    if (!f) cout << "No\n";
  }
}
