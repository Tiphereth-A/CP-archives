#include <bits/stdc++.h>
using namespace std;
int main() {
  int m, n;
  cin >> m >> n;
  vector<int> a, ans;
  for (int i = 1, _; i <= m + n; ++i) {
    cin >> _;
    a.push_back(_);
  }
  sort(a.begin(), a.end());
  for (auto it = a.begin(); it != a.end(); ++it) {
    if (it == a.end() - 1) {
      ans.push_back(*it);
      continue;
    }
    if (*it == *(it + 1)) {
      ++it;
      continue;
    }
    ans.push_back(*it);
  }
  for (auto it = ans.begin(); it != ans.end(); ++it)
    cout << *it << " \n"[it == ans.end() - 1];
  return 0;
}
