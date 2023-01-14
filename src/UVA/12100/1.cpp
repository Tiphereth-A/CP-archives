#include <bits/stdc++.h>
using namespace std;
int c[10];
bool check(int x) {
  for (int i = x + 1; i < 10; i++)
    if (c[i] > 0) return false;
  return true;
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    for (int i = 0; i < 10; i++) c[i] = 0;
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i) c[v[i]]++;
    int top = 0;
    int cnt = 0;
    while (top < v.size()) {
      if (check(v[top])) {
        cnt++;
        c[v[top]]--;
        if (top == m) break;
        top++;
      } else {
        v.push_back(v[top]);
        if (top == m) m = v.size() - 1;
        top++;
      }
    }
    cout << cnt << '\n';
  }
  return 0;
}
