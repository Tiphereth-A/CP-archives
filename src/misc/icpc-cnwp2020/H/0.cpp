#include <bits/stdc++.h>
using ll = long long;
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
int _w, _t;
ll a, b, c;
using namespace std;
ll gcd(ll u, ll v) { return v ? gcd(v, u % v) : u; }
void solve() {
  scanf("%lld%lld%lld", &a, &b, &c);
  ll ans = a * b / gcd(a, b);
  ll g = gcd(ans, c);
  ans = ans * c / g;
  printf("%lld\n", ans);
}
int main() {
  solve();
  return 0;
}
