#include <bits/stdc++.h>
using namespace std;
namespace Util {
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t d = floor(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
constexpr int64_t pow_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t res(1);
  a %= mod;
  for (; b; b >>= 1, a = mul_mod(a, a, mod))
    if (b & 1) res = mul_mod(res, a, mod);
  return res;
}
constexpr int64_t qpow(int64_t a, int64_t b, const int64_t &mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int64_t string2int(const string &s, const int64_t &mod) {
  if (s.size() < 18) return stoll(s) % mod;
  int64_t ans = 0;
  for (auto it = s.begin(); it != s.end(); ++it)
    ((ans *= 10) += (*it) - '0') %= mod;
  return ans;
}
namespace Primetest_miller_rabin {
constexpr uint64_t bases[] = {2, 3};
constexpr bool is_prime(uint64_t n) {
  if (n <= 1) return false;
  for (uint64_t a : bases)
    if (n == a) return true;
  if (n % 2 == 0) return false;
  uint64_t d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (uint64_t a : bases) {
    uint64_t t = d, y = pow_mod(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod(y, y, n);
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) return false;
  }
  return true;
}
}  // namespace Primetest_miller_rabin
using Primetest_miller_rabin::is_prime;
pr_13123111 = 6, pr_1515343657 = 5;
const int64_t pf_998244352[] = {2, 7, 17},
              pf_13123110[] = {2, 3, 5, 7, 11, 13, 19, 23},
              pf_1515343656[] = {2, 3, 4003, 15773};
}  // namespace Util
namespace _1_9 {
using namespace ::Util;
const int64_t p = 998244353;
const int64_t phi_p = p - 1;
void main() {
  int n;
  cin >> n;
  string _;
  for (int i = 0; i < n; ++i) {
    cin >> _;
    cout << pow_mod(19, string2int(_, phi_p), p) << '\n';
  }
}
}  // namespace _1_9
namespace _1_q {
using namespace ::Util;
const int64_t p = 1145141;
const int64_t phi_p = p - 1;
void main() {
  int n;
  cin >> n;
  string _;
  for (int i = 0; i < n; ++i) {
    cin >> _;
    cout << pow_mod(19, string2int(_, phi_p), p) << '\n';
  }
}
}  // namespace _1_q
namespace _1_qp {
using namespace ::Util;
const int64_t p = 5211600617818708273ll;
const int64_t phi_p = p - 1;
void main() {
  int n;
  cin >> n;
  int64_t _;
  for (int i = 0; i < n; ++i) {
    cin >> _;
    cout << pow_mod(19, _ % phi_p, p) << '\n';
  }
}
}  // namespace _1_qp
namespace _1_w9 {
using namespace ::Util;
const int p = 998244353;
const int x = 55244, y = 45699;
int res[x + y + 1] = {1};
void main() {
  for (int i = 1; i <= x + y; ++i)
    res[i] = (int)((unsigned)(res[i - 1]) * 19) % p;
  int n;
  cin >> n;
  int64_t _;
  for (int i = 0; i < n; ++i) {
    cin >> _;
    cout << res[_ <= x ? _ : (_ - x) % y + x] << '\n';
  }
}
}  // namespace _1_w9
namespace _2_p {
using namespace ::Util;
const int N = 1e6 + 1, P = 78498 + 1;
bool vis[N];
int64_t prime[P], cnt_prime;
void init_prime(const int &n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt_prime] = i;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
bool vis2[N];
void main() {
  init_prime();
  int n;
  cin >> n;
  int64_t l, r;
  for (int i = 0; i < n; ++i) {
    cin >> l >> r;
    if (r < N) {
      for (int i = l; i <= r; ++i) cout << "p."[vis[i]];
    } else {
      for (int i = 1; i <= cnt_prime; ++i)
        for (int64_t j = (int64_t)ceil(1.0l * l / prime[i]) * prime[i]; j <= r;
             j += prime[i])
          vis2[j - l] = 1;
      if (r <= (int64_t)(N - 1) * (N - 1))
        for (int i = 0; i <= r - l; ++i) cout << "p."[vis2[i]];
      else
        for (int i = 0; i <= r - l; ++i)
          cout << "p."[vis2[i] || !is_prime(i + l)];
    }
    cout << '\n';
  }
}
}  // namespace _2_p
namespace _2_u {
using namespace ::Util;
const int N = 1e6 + 1, P = 78498 + 1;
bool vis[N];
int64_t prime[P], cnt_prime;
int mu[N];
void init_prime(const int &n = N - 1) {
  mu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) mu[prime[++cnt_prime] = i] = -1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
}
int mu2[N];
int64_t _x[N];
void main() {
  init_prime();
  int n;
  cin >> n;
  int64_t l, r;
  for (int i = 0; i < n; ++i) {
    cin >> l >> r;
    if (r < N) {
      for (int i = l; i <= r; ++i) cout << "-0+"[mu[i] + 1];
    } else {
      for (int i = 0; i <= r - l; ++i) {
        mu2[i] = 1;
        _x[i] = i + l;
      }
      for (int i = 1; i <= cnt_prime; ++i)
        for (int64_t j = (int64_t)ceil(1.0l * l / prime[i]) * prime[i]; j <= r;
             j += prime[i]) {
          if (j % (prime[i] * prime[i])) {
            mu2[j - l] *= -1;
            _x[j - l] /= prime[i];
          } else mu2[j - l] = 0;
        }
      if (r <= (int64_t)(N - 1) * (N - 1)) {
        for (int i = 0; i <= r - l; ++i)
          if (_x[i] != 1) mu2[i] *= -1;
      } else {
        int64_t __ = 0;
        for (int i = 0; i <= r - l; ++i)
          if (mu2[i] && _x[i] != 1) {
            if ((__ = sqrtl(_x[i])) * __ == _x[i]) mu2[i] = 0;
            else if (is_prime(_x[i])) mu2[i] *= -1;
          }
      }
      for (int i = 0; i <= r - l; ++i) cout << "-0+"[mu2[i] + 1];
    }
    cout << '\n';
  }
}
}  // namespace _2_u
namespace _2_g {
using namespace ::Util;
const int p1 = 998244353, p2 = 13123111;
int ord2[p2];
bool not_coprime[p2];
void init() {
  for (int i = 1, p = pr_13123111; i < p2; ++i) {
    ord2[p] = i;
    (p *= pr_13123111) %= p2;
  }
  for (int i : pf_13123110)
    for (int j = i; j < p2; j += i) not_coprime[j] = 1;
}
void main() {
  init();
  int n;
  cin >> n;
  int64_t l, r, p;
  for (int i = 0; i < n; ++i) {
    cin >> l >> r >> p;
    if (p == p2)
      for (auto i = l; i <= r; ++i) cout << "g."[not_coprime[ord2[i]]];
    else
      for (auto i = l; i <= r; ++i) {
        bool f = 0;
        for (auto j : pf_998244352)
          if (qpow(i, (p1 - 1) / j, p1) == 1) {
            f = 1;
            break;
          }
        cout << "g."[f];
      }
    cout << '\n';
  }
}
}  // namespace _2_g
namespace _2_gq {
using namespace ::Util;
const int64_t p1 = 998244353, p2 = 1515343657;
void main() {
  int n;
  cin >> n;
  int64_t l, r;
  string _;
  for (int i = 0; i < n; ++i) {
    cin >> l >> r >> _;
    if (_.front() == '?') {
      for (auto i = l; i <= r; ++i) {
        bool f = 0;
        for (auto j : pf_1515343656)
          if (qpow(i, (p2 - 1) / j, p2) == 1) {
            f = 1;
            break;
          }
        cout << "g."[f];
      }
    } else {
      for (auto i = l; i <= r; ++i) {
        bool f = 0;
        for (auto j : pf_998244352)
          if (qpow(i, (p1 - 1) / j, p1) == 1) {
            f = 1;
            break;
          }
        cout << "g."[f];
      }
    }
    cout << '\n';
  }
}
}  // namespace _2_gq
#define _run_return(expressions) return (expressions), 0
int main() {
  auto st = clock();
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  string _;
  getline(cin, _);
  if (_ == "1_998244353") _run_return(_1_9::main());
  if (_ == "1?") _run_return(_1_q::main());
  if (_ == "1?+") _run_return(_1_qp::main());
  if (_ == "1wa_998244353") _run_return(_1_w9::main());
  if (_ == "2p") _run_return(_2_p::main());
  if (_ == "2u") _run_return(_2_u::main());
  if (_ == "2g") _run_return(_2_g::main());
  if (_ == "2g?") _run_return(_2_gq::main());
  return 1;
}
