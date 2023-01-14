#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
const int KASE = 1;
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (int)(n % 10);
  return os;
}
ostream &operator<<(ostream &os, u128 n) {
  if (n > 9) os << (u128)(n / 10);
  os << (int)(n % 10);
  return os;
}
namespace Subtask1 {
void main() {
  u64 a, b, c;
  for (int i = 0; i < 10; ++i) {
    cin >> a >> b >> c;
    cout << (u128)a * b % c << '\n';
  }
}
}  // namespace Subtask1
namespace Subtask2 {
struct mat {
  i128 data[3][3];
  u64 p;
  void clear() {
    this->p = 0;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) this->data[i][j] = 0;
  }
  mat &operator*=(const mat &rhs) {
    mat ret;
    ret.clear();
    ret.p = this->p;
    for (int i = 0; i < 3; ++i)
      for (int k = 0; k < 3; ++k)
        for (int j = 0; j < 3; ++j)
          ret.data[i][j] =
            (ret.data[i][j] + this->data[i][k] * rhs.data[k][j] % this->p) %
            this->p;
    return *this = ret;
  };
} a, b;
void main() {
  for (int i = 0; i < 10; ++i) {
    u64 n, p;
    cin >> n >> p;
    a.clear();
    b.clear();
    b.data[0][2] = b.data[1][1] = b.data[2][2] = b.data[2][1] = b.data[2][0] =
      a.data[0][2] = 1;
    b.data[1][2] = 2;
    a.p = b.p = p;
    for (; n; n >>= 1, b *= b)
      if (n & 1) a *= b;
    cout << ((a.data[0][0] - a.data[0][1] * 2 + a.data[0][2]) % p + p) % p
         << endl;
  }
}
}  // namespace Subtask2
namespace Subtask3 {
const u64 inv3 = 12297829382473034411ull, inv5 = 14757395258967641293ull;
void main() {
  u64 n;
  cin >> n;
  u64 s0 = n + 1, s1 = (u128)n * (n + 1) / 2, s2 = s1 * (2 * n + 1) * inv3,
      s3 = s1 * s1, s4 = s2 * inv5 * (3 * n * n + 3 * n - 1);
  cout << s0 << '\n'
       << s0 << '\n'
       << s1 << '\n'
       << s1 << '\n'
       << s2 << '\n'
       << s2 << '\n'
       << s3 << '\n'
       << s3 << '\n'
       << s4 << '\n'
       << s4 << '\n';
}
}  // namespace Subtask3
namespace Subtask4 {
const int N = 5000, inf = 0x3F3F3F3F;
int n, m, type;
bool data[N + 11][N + 11];
int seed;
int next_rand() {
  static const int P = 1000000007, Q = 83978833, R = 8523467;
  return seed = ((i64)Q * seed % P * seed + R) % P;
}
void generate_input() {
  cin >> n >> m >> type;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) data[i][j] = bool((next_rand() % 8) > 0);
}
u64 count1() {
  u64 ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) ans += data[i][j];
  return ans * (ans - 1);
}
using dis_type = i64[N + 11][N + 11];
dis_type dis, dis2;
i64 get_dis(const dis_type &dis, int x, int y) {
  if (x < 0 || y < 0 || x >= n || y >= m) return inf;
  return dis[x][y];
}
#define _clr(dis)             \
  for (int i = 0; i < n; ++i) \
    for (int j = 0; j < m; ++j) dis[i][j] = inf
i64 count2() {
  _clr(dis);
  _clr(dis2);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (data[i][j]) {
        dis2[i][j] = min(get_dis(dis2, i - 1, j), get_dis(dis2, i, j - 1)) + 1;
        dis[i][j] = min(dis[i][j], dis2[i][j]);
      } else dis2[i][j] = 0;
  _clr(dis2);
  for (int i = 0; i < n; ++i)
    for (int j = m - 1; j >= 0; --j)
      if (data[i][j]) {
        dis2[i][j] = min(get_dis(dis2, i - 1, j), get_dis(dis2, i, j + 1)) + 1;
        dis[i][j] = min(dis[i][j], dis2[i][j]);
      } else dis2[i][j] = 0;
  _clr(dis2);
  for (int i = n - 1; i >= 0; --i)
    for (int j = 0; j < m; ++j)
      if (data[i][j]) {
        dis2[i][j] = min(get_dis(dis2, i + 1, j), get_dis(dis2, i, j - 1)) + 1;
        dis[i][j] = min(dis[i][j], dis2[i][j]);
      } else dis2[i][j] = 0;
  _clr(dis2);
  for (int i = n - 1; i >= 0; --i)
    for (int j = m - 1; j >= 0; --j)
      if (data[i][j]) {
        dis2[i][j] = min(get_dis(dis2, i + 1, j), get_dis(dis2, i, j + 1)) + 1;
        dis[i][j] = min(dis[i][j], dis2[i][j]);
      } else dis2[i][j] = 0;
  i64 ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (data[i][j]) ans += dis[i][j];
  return ans;
}
#undef _clr
void main() {
  cin >> seed;
  for (int i = 0; i < 10; ++i) {
    generate_input();
    cout << (type == 1 ? count2() : count1()) << endl;
  }
}
}  // namespace Subtask4
namespace Subtask5 {
using Subtask4::data;
using Subtask4::m;
using Subtask4::n;
using Subtask4::seed;
using s_type = Subtask4::dis_type;
using Subtask4::next_rand;
s_type s;
void generate_input() {
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) data[i][j] = bool((next_rand() % 8) > 0);
}
i64 count3() {
  i64 ans = 0;
  for (int j = 0; j < m; ++j) s[0][j] = data[0][j];
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j) s[i][j] = data[i][j] * (s[i - 1][j] + 1);
  stack<pair<i64, i64>> stk;
  i64 ans2 = 0;
  for (int i = 0; i < n; ++i) {
    while (!stk.empty()) stk.pop();
    ans2 = 0;
    for (int j = 0; j < m; ++j) {
      if (!s[i][j]) {
        while (!stk.empty()) stk.pop();
        ans2 = 0;
        continue;
      }
      i64 size = 1;
      while (!stk.empty() && stk.top().first >= s[i][j]) {
        size += stk.top().second;
        ans2 -= stk.top().first * stk.top().second;
        stk.pop();
      }
      stk.emplace(s[i][j], size);
      ans += (ans2 += s[i][j] * size);
    }
  }
  return ans;
}
void main() {
  cin >> seed;
  for (int i = 0; i < 10; ++i) {
    generate_input();
    cout << count3() << endl;
  }
}
}  // namespace Subtask5
namespace Subtask6 {
constexpr u64 next(const u64 &t, const u64 &a, const u64 &b, const u64 &c) {
  return (t * t * a + b) % c;
}
void main() {
  u64 n, a, b, c;
  for (int i = 0; i < 10; ++i) {
    cin >> n >> a >> b >> c;
    u64 k1 = 0, k2 = 2;
    u64 t1 = 0, t2 = 0;
    while (true) {
      t2 = next(t2, a, b, c);
      ++k1;
      if (t1 == t2) break;
      if (k1 == k2) {
        k1 = 0;
        k2 <<= 1;
        t1 = t2;
      }
    }
    u64 cyc_len = k1;
    t1 = t2 = 0;
    u64 k = 1;
    for (k = 1; k <= cyc_len; ++k) t1 = next(t1, a, b, c);
    for (k = 1; t1 != t2; ++k) {
      t1 = next(t1, a, b, c);
      t2 = next(t2, a, b, c);
    }
    for (k2 = (n - k) % cyc_len + 1, k = 1; k <= k2; ++k)
      t1 = next(t1, a, b, c);
    cout << t1 << endl;
  }
}
}  // namespace Subtask6
namespace Subtask7 {
int g[16][16];
bool ln[16][17], col[16][17], zon[16][17];
constexpr int getz(int x, int y) { return (x / 4) * 4 + (y / 4); }
bool _;
void dfs(int x, int y) {
  if (x == -1) {
    _ = true;
    return;
  }
  if (!_)
    if (g[x][y]) {
      y ? dfs(x, y - 1) : dfs(x - 1, 15);
    } else {
      auto now_l = ln[x], now_c = col[y], now_z = zon[getz(x, y)];
      for (int i = 1; i <= 16; ++i) {
        if (!(now_l[i] && now_c[i] && now_z[i])) continue;
        now_l[i] ^= true;
        now_c[i] ^= true;
        now_z[i] ^= true;
        g[x][y] = i;
        y ? dfs(x, y - 1) : dfs(x - 1, 15);
        if (!_) {
          g[x][y] = 0;
          now_l[i] ^= true;
          now_c[i] ^= true;
          now_z[i] ^= true;
        }
      }
    }
}
void solve(int points) {
  for (int i = 0; i < 16; ++i)
    for (int j = 0; j <= 16; ++j) ln[i][j] = col[i][j] = zon[i][j] = true;
  for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j) {
      char __;
      cin >> __;
      if (__ != '?') {
        __ -= 'A' - 1;
        g[i][j] = __;
        ln[i][__] ^= true;
        col[j][__] ^= true;
        zon[getz(i, j)][__] ^= true;
      } else g[i][j] = 0;
    }
  _ = false;
  dfs(15, 15);
  if (_)
    for (int k = 0; k <= points - 1; ++k) {
      for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j) cout << char(g[i][j] + 'A' - 1);
      cout << endl;
    }
  else
    for (int k = 0; k <= points - 1; ++k) cout << "NO SOLUTION." << endl;
}
void main() {
  solve(1);
  solve(2);
  solve(3);
  solve(4);
}
}  // namespace Subtask7
namespace Subtask8 {
const u64 p = 1234567891;
const u64 inv24 = 257201644, inv36 = 582990393, inv48 = 128600822,
          inv60 = 596707814, inv144 = 454389571, inv240 = 766460899,
          inv360 = 922496563, inv5040 = 330442874;
void main() {
  u64 n;
  cin >> n;
  n %= p;
  cout << (n > 6) * (n * (n - 1) % p * (n - 2) % p * (n - 3) % p * (n - 4) % p *
                     (n - 5) % p * (n - 6) % p * inv5040 % p)
       << '\n'
       << (n > 1) * ((n - 1) * (n - 1) % p * n % p * n % p * (2 * n - 1) % p *
                     (2 * n % p * n % p - 2 * n % p + 1 + p) % p * inv60 % p)
       << '\n'
       << (n > 2) * (n * n % p * (n - 1) % p * (n - 1) % p * (n - 2) % p *
                     (2 * n - 1) % p * (7 * n - 3) % p * inv360 % p)
       << '\n'
       << (n > 2) * (n * n % p * n % p * (n - 1) % p * (n - 1) % p * (n - 2) %
                     p * (3 * n - 1) % p * inv48 % p)
       << '\n'
       << (n > 3) * (n * n % p * n % p * n % p * (n - 1) % p * (n - 2) % p *
                     (n - 3) % p * inv24 % p)
       << '\n'
       << (n > 2) * (n * n % p * n % p * (n - 1) % p * (n - 2) % p *
                     (3 * n * n % p - 6 * n % p + 1 + p) % p * inv60 % p)
       << '\n'
       << (n > 3) * (n * n % p * (n - 1) % p * (n - 2) % p * (n - 3) % p *
                     (5 * n * n % p - 9 * n % p + 1 + p) % p * inv360 % p)
       << '\n'
       << (n > 1) * (n * n % p * (n - 1) % p * (n - 1) % p * (2 * n - 1) % p *
                     (5 * n % p * n % p - 5 * n % p + 2 + p) % p * inv144 % p)
       << '\n'
       << (n > 2) * (n * n % p * n % p * (n - 1) % p * (n - 1) % p * (n - 2) %
                     p * (2 * n - 1) % p * inv36 % p)
       << '\n'
       << (n > 3) * (n * n % p * (n - 1) % p * (n - 1) % p * (n - 2) % p *
                     (n - 3) % p * (2 * n - 3) % p * inv240 % p)
       << '\n';
}
}  // namespace Subtask8
namespace Subtask9 {
void main() {
  cout << "1984\n"
          "123456\n"
          "chenlijie\n"
          "$_$\n"
          "we\n"
          "hold\n"
          "these\n"
          "truths\n"
          "to be\n"
          "selfevident\n";
}
}  // namespace Subtask9
namespace Subtask10 {
const function<void(u64 &, u64 &)> func[] = {
  [](u64 &a, u64 &b) { a += b * 26ull; },
  [](u64 &a, u64 &b) { a += b * 651ull; },
  [](u64 &a, u64 &b) { a += b * 15651ull; },
  [](u64 &a, u64 &b) { a += b * 360651ull; },
  [](u64 &a, u64 &b) { a += b * 7950651ull; },
  [](u64 &a, u64 &b) { a += b * 167340651ull; },
  [](u64 &a, u64 &b) { a += b * 3355140651ull; },
  [](u64 &a, u64 &b) { a += b * 63923340651ull; },
  [](u64 &a, u64 &b) { a += b * 1154150940651ull; },
  [](u64 &a, u64 &b) { a += b * 19688020140651ull; },
  [](u64 &a, u64 &b) { a += b * 316229927340651ull; },
  [](u64 &a, u64 &b) { a += b * 4764358535340651ull; },
  [](u64 &a, u64 &b) { a += b * 67038159047340651ull; },
  [](u64 &a, u64 &b) { a += b * 876597565703340651ull; },
  [](u64 &a, u64 &b) { a += b * 10591310445575340651ull; },
  [](u64 &a, u64 &b) { a += b * 6772687681910030955ull; },
  [](u64 &a, u64 &b) { a += b * 5479948192676037227ull; },
  [](u64 &a, u64 &b) { a += b * 12292036863279645291ull; },
  [](u64 &a, u64 &b) { a += b * 11448514006979854955ull; },
  [](u64 &a, u64 &b) { a += b * 5543854012881322603ull; },
  [](u64 &a, u64 &b) { a += b * 7009382195709231723ull; },
  [](u64 &a, u64 &b) { a += b * 14337023109848777323ull; },
  [](u64 &a, u64 &b) { a += b * 6754098618987856491ull; },
  [](u64 &a, u64 &b) { a += b * 2452069220114645611ull; },
  [](u64 &a, u64 &b) { a += b * 12294754496077775467ull; },
  [](u64 &a, u64 &b) { a += b * 3690695698331353707ull; }};
const int recusion[][26] = {
  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
  {128, 0,    0, 0, 0,    0, 1376, 576, 2208, 0, 0, 576, 128,
   0,   2208, 0, 0, 2568, 0, 1376, 0,   0,    0, 0, 0,   0},
  {9, 8,  20, 2, 10, 2, 2, 3,  26, 8,  8, 4, 26,
   8, 36, 20, 8, 24, 8, 2, 40, 8,  20, 2, 4, 8},
  {7304709, 384591,   1220093, 1822275, 9884647, 308820,   3398404,
   486395,  10216758, 3560,    504386,  1741038, 1734502,  12420932,
   3951484, 2651226,  10240,   5363041, 9103033, 12706140, 3390299,
   415290,  971012,   8118,    10294,   50216}};
const int output_recusion[] = {1, 2, 2, 5};
void main() {
  u64 a, b;
  for (int i = 0; i < 4; ++i) {
    cin >> b;
    a = 0;
    for (int j = 0; j < 26; ++j)
      for (int k = 0; k < recusion[i][j]; ++k) func[j](a, b);
    for (int j = 0; j < output_recusion[i]; ++j) cout << a << '\n';
  }
}
}  // namespace Subtask10
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  static void (*func[])(void) = {Subtask1::main,
                                 Subtask2::main,
                                 Subtask3::main,
                                 Subtask4::main,
                                 Subtask5::main,
                                 Subtask6::main,
                                 Subtask7::main,
                                 Subtask8::main,
                                 Subtask9::main,
                                 Subtask10::main};
  func[KASE - 1]();
  return 0;
}
