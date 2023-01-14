#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _mem(a) memset(a, 0, sizeof(a))
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  int f = 0;
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  if (f) x = -x;
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
  print(oth...);
}
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
const int N = 1e2 + 1;
const int MOD = 1e9 + 7;
i64 n;
std::bitset<N> b1, b2;
int cnt, arr[N];
struct mat {
  int num[N][N];
  void operator*=(const mat &a) {
    int c[N][N];
    _mem(c);
    _rep(i, 1, N) _rep(j, 1, N) {
      int &tmp = c[i][j];
      _rep(k, 1, N) tmp = ((i64)num[i][k] * a.num[k][j] + tmp) % MOD;
    }
    memcpy(num, c, sizeof(num));
  }
} a;
struct col_vector {
  int num[N];
  void operator*=(const mat &a) {
    int c[N];
    _mem(c);
    _rep(i, 1, N) {
      int &tmp1 = c[i];
      const int *tmp2 = a.num[i];
      _rep(j, 1, N) tmp1 = ((i64)num[j] * tmp2[j] + tmp1) % MOD;
    }
    memcpy(num, c, sizeof(num));
  }
} dp;
void pow(mat a, i64 b, col_vector &ret) {
  for (; b; b >>= 1, a *= a)
    if (b & 1) ret *= a;
}
int main() {
  int k, p;
  read(n);
  read(k);
  while (k--) {
    read(p);
    b1[p] = 1;
  }
  read(k);
  while (k--) {
    read(p);
    b2[p] = 1;
  }
  b1 &= b2;
  int *tmp = a.num[100];
  _rep(i, 1, N) {
    if (b1[i]) {
      tmp[101 - i] = dp.num[i] = 1;
      arr[++cnt] = i;
    }
  }
  _rep(i, 1, 100) a.num[i][i + 1] = 1;
  _for(i, 1, Min(100ll, n)) {
    _for(j, 1, cnt) {
      if (i - arr[j] > 0)
        dp.num[i] = ((i64)dp.num[i] + dp.num[i - arr[j]]) % MOD;
      else break;
    }
  }
  if (n <= 100) print(dp.num[n]);
  else {
    pow(a, n - 100, dp);
    print(dp.num[100]);
  }
  FastIO::flush();
  return 0;
}
