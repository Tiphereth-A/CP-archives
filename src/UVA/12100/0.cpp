#include <bits/stdc++.h>
using namespace std;
int c[10];
bool chk(int x) {
  for (int i = x + 1; i < 10; ++i)
    if (c[i]) return 0;
  return 1;
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    for (int i = 0; i < 10; ++i) c[i] = 0;
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i) ++c[v[i]];
    int top = 0;
    int cnt = 0;
    while (top < v.size()) {
      if (chk(v[top])) {
        ++cnt;
        if (top == m) break;
        --c[v[top]];
      } else {
        v.push_back(v[top]);
        if (top == m) m = v.size() - 1;
      }
      ++top;
    }
    cout << cnt << '\n';
  }
}
