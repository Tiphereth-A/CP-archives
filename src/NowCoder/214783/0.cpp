#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
bool vis[N];
int prime[N], cnt_prime;
int phi[N];
void init(int n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) phi[prime[++cnt_prime] = i] = i - 1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      phi[i * prime[j]] = phi[i] * prime[j];
      if (i % prime[j] == 0) break;
      phi[i * prime[j]] -= phi[i];
    }
  }
}
int main() {
  init();
  int n;
  cin >> n;
  long long a = 0, b = n - (n % 2 == 0);
  for (int i = 1; i <= n; ++i) a += phi[i];
  long long g = gcd(a, b);
  cout << a / g << '/' << b / g;
  return 0;
}
