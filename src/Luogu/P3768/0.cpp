#include <bits/stdc++.h>
using namespace std;
using data_type = long long;
const int N = 3e6 + 1, P = N / 10 + 1;
data_type sf[N];
unordered_map<data_type, data_type> sum_f;
data_type prime[P], prime2[P], prime3[P], cnt;
bool vis[N];
void init(const data_type &p, const data_type &n = N - 1) {
  sf[1] = 1;
  for (data_type i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      prime3[cnt] = (prime2[cnt] = i * i % p) * i % p;
      sf[i] = (prime3[cnt] + p - prime2[cnt]) % p;
    }
    for (data_type j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sf[i * prime[j]] = sf[i] * prime3[j] % p;
      if (i % prime[j] == 0) break;
      (sf[i * prime[j]] += p - sf[i] * prime2[j]) %= p;
    }
  }
  for (data_type i = 2; i <= n; ++i) (sf[i] += sf[i - 1]) %= p;
}
constexpr data_type g(data_type n, const data_type &p) {
  n %= p;
  return n * n % p;
}
constexpr data_type inv3(const data_type &p) {
  return (p + p * (p % 3 == 1) + 1) / 3;
};
constexpr data_type sum_g(data_type n, const data_type &p) {
  n %= p;
  return n * (n + 1) / 2 % p * (2 * n + 1) % p * inv3(p) % p;
}
constexpr data_type sum_conv_g_f(data_type n, const data_type &p) {
  n %= p;
  data_type _ = n * (n + 1) / 2 % p;
  return _ * _ % p;
}
data_type get_sum_f_mul_g1(const data_type &n, const data_type &p) {
  if (n < N) return sf[n];
  if (sum_f[n]) return sum_f[n];
  data_type ans = sum_conv_g_f(n, p);
  for (data_type l = 2, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans += p - (sum_g(r, p) + p - sum_g(l - 1, p)) % p *
                  get_sum_f_mul_g1(n / l, p) % p) %= p;
  }
  return sum_f[n] = ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  data_type n, p;
  cin >> p >> n;
  init(p);
  data_type ans = 0;
  for (data_type l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans += (get_sum_f_mul_g1(r, p) + p - get_sum_f_mul_g1(l - 1, p)) % p *
            sum_conv_g_f(n / l, p) % p) %= p;
  }
  cout << ans << '\n';
  return 0;
}
