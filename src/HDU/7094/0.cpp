#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    int n, k;
    cin >> n >> k;
    cout << (n == 1 || k == 2 || (~k & 1 && n != k) ? "No!" : "Yes!") << '\n';
  }
  return 0;
}
