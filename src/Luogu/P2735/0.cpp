#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, p;
  cin >> n >> m >> p;
  cout << (p * m) / 2 - (gcd(n, m) + gcd(abs(p - n), m) + p) / 2 + 1;
  return 0;
}
