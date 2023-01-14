#include <bits/stdc++.h>
typedef long long ll;
std::pair<ll, ll> exgcd(ll a, ll b) {
  if (b == 0) return std::make_pair(1, 0);
  std::pair<ll, ll> temp = exgcd(b, a % b);
  std::pair<ll, ll> ans =
    std::make_pair(temp.second, temp.first - a / b * temp.second);
  return ans;
}
int main() {
  ll a, b;
  scanf("%lld%lld", &a, &b);
  std::pair<ll, ll> point = exgcd(a, b);
  printf("%lld\n", (point.first + b) % b);
  return 0;
}
