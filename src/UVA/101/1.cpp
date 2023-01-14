#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> piles;
pair<int, int> find(int a) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < piles[i].size(); ++j)
      if (piles[i][j] == a) return {i, j};
}
void clear(int p, int h) {
  for (int i = h + 1; i < piles[p].size(); ++i) {
    int tmp = piles[p][i];
    piles[tmp].push_back(tmp);
  }
  piles[p].resize(h + 1);
}
void pile(int p, int h, int b) {
  for (int i = h; i < piles[p].size(); ++i) piles[b].push_back(piles[p][i]);
  piles[p].resize(h);
}
int main() {
  cin >> n;
  piles.resize(n);
  for (int i = 0; i < n; ++i) piles[i].push_back(i);
  string s1, s2;
  int a, b;
  while (cin >> s1) {
    if (s1 == "quit") break;
    cin >> a >> s2 >> b;
    int pa, pb, ha, hb;
    {
      auto p = find(a);
      pa = p.first;
      ha = p.second;
    }
    {
      auto p = find(b);
      pb = p.first;
      hb = p.second;
    }
    if (pa == pb) continue;
    if (s1 == "move") clear(pa, ha);
    if (s2 == "onto") clear(pb, hb);
    pile(pa, ha, pb);
  }
  for (int i = 0; i < n; ++i) {
    cout << i << ":";
    for (int j = 0; j < piles[i].size(); ++j) cout << ' ' << piles[i][j];
    cout << '\n';
  }
  return 0;
}
