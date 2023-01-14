#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 2e4 + 5;
int n, m;
int fa[N];
std::map<std::string, int> id;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[fa[fa[fa[x]]]]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  cin >> n >> m;
  std::string str1, str2;
  for (int i = 1; i <= n; ++i) {
    cin >> str1;
    id[str1] = fa[i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    cin >> str1 >> str2;
    merge(id[str1], id[str2]);
  }
  int k;
  cin >> k;
  for (int i = 1; i <= k; ++i) {
    cin >> str1 >> str2;
    cout << (find(id[str1]) == find(id[str2]) ? "Yes." : "No.") << endl;
  }
  return 0;
}
