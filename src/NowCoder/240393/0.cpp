#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  int cnt = 0;
  vector<int> v;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    if (!v.empty() && (v.back() == x || v.back() + x == k)) {
      v.pop_back();
      ++cnt;
      continue;
    }
    v.push_back(x);
  }
  int l = 0, r = v.size() - 1;
  while (l < r && (v[l] == v[r] || v[l] + v[r] == k)) {
    ++cnt;
    ++l;
    --r;
  }
  cout << cnt << '\n';
  return 0;
}
