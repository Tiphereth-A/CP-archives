#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;
const int N = 100010;
int T;
int tr[N][20], idx;
void insert(string s) {
  int p = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    int u = s[i] - '0';
    if (!tr[p][u]) tr[p][u] = ++idx;
    p = tr[p][u];
  }
}
vector<int> cnt;
map<string, vector<string>> ans;
vector<string> res;
void dfs(int u) {
  int f = 0;
  for (int i = 0; i < 10; i++) {
    if (tr[u][i]) {
      cnt.push_back(i);
      dfs(tr[u][i]);
      cnt.pop_back();
      f = 1;
    }
  }
  if (f == 0) {
    string t = "";
    for (int i = cnt.size() - 1; i >= 0; i--) t += cnt[i] + '0';
    res.push_back(t);
  }
}
void f(set<string> x) {
  res.clear();
  memset(tr, 0, sizeof tr);
  idx = 0;
  for (auto i : x) { insert(i); }
  dfs(0);
}
int main() {
  ios::sync_with_stdio(false);
  T = 1;
  while (T--) {
    map<string, set<string>> g;
    int n;
    cin >> n;
    while (n--) {
      string op;
      cin >> op;
      int m;
      cin >> m;
      while (m--) {
        string num;
        cin >> num;
        g[op].insert(num);
      }
    }
    for (auto i : g) {
      f(i.second);
      ans[i.first] = res;
    }
    cout << ans.size() << endl;
    for (auto i : ans) {
      cout << i.first << ' ';
      cout << i.second.size() << ' ';
      for (auto j : i.second) cout << j << ' ';
      cout << endl;
    }
  }
}
