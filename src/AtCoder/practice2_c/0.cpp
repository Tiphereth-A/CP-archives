#include <bits/stdc++.h>
using namespace std;
#include <atcoder/math.hpp>
using namespace atcoder;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << floor_sum(n, m, a, b) << '\n';
  }
  return 0;
}
