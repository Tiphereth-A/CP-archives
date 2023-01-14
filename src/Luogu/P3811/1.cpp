#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e6 + 5;
typedef long long ll;
ll inv[MAXN];
int main() {
  ios::sync_with_stdio(false);
  cout.tie(nullptr);
  inv[1] = 1;
  int n, p;
  cin >> n >> p;
  for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
  for (int i = 1; i <= n; i++) cout << inv[i] << '\n';
  return 0;
}
