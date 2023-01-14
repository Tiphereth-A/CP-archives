#include <bits/stdc++.h>
using namespace std;
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
#define _next(x) (((x ^= x << 13) ^= x >> 17) ^= x << 5)
#define _expanded_rep(len, repp, expressions) \
  {                                           \
    repp = len >> 3;                          \
    while (repp--) {                          \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
      { expressions }                         \
    }                                         \
    switch (len & 7) {                        \
      case 7: {                               \
        expressions                           \
      }                                       \
      case 6: {                               \
        expressions                           \
      }                                       \
      case 5: {                               \
        expressions                           \
      }                                       \
      case 4: {                               \
        expressions                           \
      }                                       \
      case 3: {                               \
        expressions                           \
      }                                       \
      case 2: {                               \
        expressions                           \
      }                                       \
      case 1: {                               \
        expressions                           \
      }                                       \
    }                                         \
  }
void output_arr(u32 *a, u32 &&size) {
  u32 ret = size;
  for (u32 x = 23333333, *_ = a + (size >> 2), *i = a; i < _; ++i) {
    ret ^= *i + x;
    _next(x);
  }
  cout << ret << '\n';
}
namespace task1 {
using data_type = u32 *;
using data_type2 = u32[256];
data_type2 cnt0, cnt8, cnt16, cnt24;
data_type a, b;
u32 n, seed;
void main() {
  cin >> n >> seed;
  a = (data_type)malloc(800000000);
  b = (data_type)malloc(800000000);
  for (u32 *_ = a + n, *i = a; i < _; ++i) {
    *i = _next(seed);
    ++cnt0[seed & 255];
    ++cnt8[seed >> 8 & 255];
    ++cnt16[seed >> 16 & 255];
    ++cnt24[seed >> 24 & 255];
  }
  for (u32 i = 1; i < 256; ++i) {
    cnt0[i] += cnt0[i - 1];
    cnt8[i] += cnt8[i - 1];
    cnt16[i] += cnt16[i - 1];
    cnt24[i] += cnt24[i - 1];
  }
  for (u32 *i = a + n; --i >= a;) b[--cnt0[*i & 255]] = *i;
  for (u32 *i = b + n; --i >= b;) a[--cnt8[*i >> 8 & 255]] = *i;
  for (u32 *i = a + n; --i >= a;) b[--cnt16[*i >> 16 & 255]] = *i;
  for (u32 *i = b + n; --i >= b;) a[--cnt24[*i >> 24 & 255]] = *i;
  output_arr(a, n << 2);
  free(a);
  free(b);
}
}  // namespace task1
namespace task2 {
#define _popcntll __builtin_popcountll
using data_type = i64[64][14063];
using str_type = char *;
using query_type = i32 *;
data_type f1, f2;
void set(data_type &f, u32 &&idx) {
  if (idx < 64)
    for (u32 i = 0; i <= idx; ++i) *f[i] |= 1ull << idx - i;
  else
    for (u32 i = 0, j; i < 64; ++i)
      f[i][(idx - i) >> 6] |= 1ull << ((idx - i) & 63);
}
str_type s1, s2;
query_type q_x, q_y, q_len;
void main() {
  u32 n, q;
  cin >> n >> q;
  s1 = (str_type)malloc(n + 1);
  s2 = (str_type)malloc(n + 1);
  cin >> s1 >> s2;
  q_x = (query_type)malloc(q << 2);
  q_y = (query_type)malloc(q << 2);
  q_len = (query_type)malloc(q << 2);
  for (u32 i = 0; i < q; ++i) cin >> q_x[i] >> q_y[i] >> q_len[i];
  u32 *anss = new u32[q];
  for (u32 idx = 0, i = 0; i < n; ++i, idx += 3) set(f1, idx + s1[i] - '0');
  for (u32 idx = 0, i = 0; i < n; ++i, idx += 3)
    set(f2, idx + s2[i] - '1' + 3 * (s2[i] == '0'));
  i64 *_f1, *_f2;
  for (u32 i = 0, len, repp, ans; i < q; ++i) {
    q_x[i] *= 3;
    q_y[i] *= 3;
    q_len[i] *= 3;
    len = q_len[i] >> 6;
    repp = len >> 3;
    ans = 0;
    _f1 = task2::f1[q_x[i] & 63] + (q_x[i] >> 6);
    _f2 = task2::f2[q_y[i] & 63] + (q_y[i] >> 6);
    _expanded_rep(len, repp, ans += _popcntll(*_f1++ & *_f2++););
    anss[i] = ans + _popcntll(*_f1 & *_f2 & (1ull << (q_len[i] & 63)) - 1);
  }
  output_arr(anss, q << 2);
  free(s1);
  free(s2);
  free(q_x);
  free(q_y);
  free(q_len);
}
#undef _popcntll
}  // namespace task2
namespace task3 {
using str_type = char *;
u32 _[266666 << 1 | 1], *f = _ + 266666;
u32 n;
str_type s;
u32 solve() {
  *f = 1;
  for (u32 i = 0, m, *f0, *f1, repp; i < n; ++i) switch (s[i]) {
      case '(':
        if (i & 1) *--f = 0;
        break;
      case ')': f += i & 1 ^ 1; break;
      case '?':
        m = (min(i, n - i) >> 1) + 1;
        if (i & 1) {
          *--f = 0;
          ++m;
        }
        f1 = (f0 = f) + 1;
        _expanded_rep(m, repp, *f0 += *f1; f0 = f1++;);
    }
  return *f;
}
void main() {
  cin >> n;
  s = (str_type)malloc(n + 1);
  cin >> s;
  cout << solve() << '\n';
  free(s);
}
}  // namespace task3
void (* const _main[4])(void) = {
  nullptr, task1::main, task2::main, task3::main};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i32 task_id;
  cin >> task_id;
  return _main[task_id](), 0;
}
