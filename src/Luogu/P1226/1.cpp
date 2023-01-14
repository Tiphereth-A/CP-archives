#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll b, p, k;
ll ksm(ll num, ll a) {
  if (num == 0) return 1;
  else {
    ll tmp = ksm(num >> 1, a);
    if (num & 1) return tmp * tmp * a % k;
    else return tmp * tmp % k;
  }
}
int main() {
  cin >> b >> p >> k;
  if (b == k) printf("%lld^%lld mod %lld=0", b, p, k);
  else {
    ll a = b % k;
    ll s = ksm(p, a);
    printf("%lld^%lld mod %lld=%lld", b, p, k, s);
  }
  return 0;
}
