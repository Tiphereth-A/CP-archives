#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 5e5 + OFFSET, M = 5e5 + OFFSET, K = 21;
unordered_map<string, int> dict;
int cnt_dict;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int deg[N];
bool judge(int n) {
  int _ = 0;
  _for(i, 1, n)
    if ((_ += deg[i] % 2) > 2) return 0;
  return 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string s1, s2;
  int x, y;
  int cnt = 0;
  _for(i, 1, N - 1) fa[i] = i;
  while (cin >> s1 >> s2) {
    x = (!dict[s1]) ? dict[s1] = ++cnt_dict : dict[s1];
    y = (!dict[s2]) ? dict[s2] = ++cnt_dict : dict[s2];
    if (find(x) != find(y)) {
      ++cnt;
      merge(x, y);
    }
    ++deg[x];
    ++deg[y];
  }
  cout << (cnt >= cnt_dict - 1 && judge(cnt_dict) ? "Possible" : "Impossible");
  return 0;
}
