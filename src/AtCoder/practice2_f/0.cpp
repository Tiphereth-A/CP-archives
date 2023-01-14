#include <bits/stdc++.h>
using namespace std;
#include <atcoder/convolution.hpp>
using namespace atcoder;
int main() {
  int n, m;
  cin >> n >> m;
  vector<modint998244353> a(n), b(m);
  int x;
  for (auto &i : a) {
    cin >> x;
    i = x;
  }
  for (auto &i : b) {
    cin >> x;
    i = x;
  }
  for (auto &&i : convolution(a, b)) cout << i.val() << ' ';
  return 0;
}
