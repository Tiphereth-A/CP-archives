#include <bits/stdc++.h>
using namespace std;
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
LL T, N;
LL Prime[11] = {2, 61, 97, 7, 13, 17, 23, 29}, Ans = -1;
LL guisuMul(LL a, LL b, LL m) {
  LL d = ((long double)a / m * b + 1e-8);
  LL r = a * b - d * m;
  return r < 0 ? r + m : r;
}
LL gsm(LL a, LL b, LL p) {
  LL res = 0;
  while (b) {
    if (b & 1) res = (res + a) % p;
    a = (a + a) % p, b >>= 1;
  }
  return res;
}
LL expow(LL a, LL b, LL p) {
  if (a == 1) return 1;
  LL res = 1;
  while (b) {
    if (b & 1) res = gsm(res, a, p);
    a = gsm(a, a, p), b >>= 1;
  }
  return res;
}
LL my_max(LL a, LL b) { return a > b ? a : b; }
LL my_min(LL a, LL b) { return a < b ? a : b; }
LL qr() {
  LL k = 0;
  char c = getchar();
  while (c < '0' || c > '9') c = getchar();
  while (c <= '9' && c >= '0') k = (k << 1) + (k << 3) + c - 48, c = getchar();
  return k;
}
bool Test(LL p, LL x) {
  LL r = 0, d = x - 1;
  while (!(d & 1)) d >>= 1, ++r;
  for (LL i = expow(p, d, x), j; r; --r) {
    j = gsm(i, i, x);
    if (j == 1) {
      if (i == 1 || i == x - 1) return 1;
      return 0;
    }
    i = j;
  }
  return 0;
}
#define ctz __builtin_ctzll
LL gcd(LL a, LL b) {
  if (!a) return b;
  if (!b) return a;
  int t = ctz(a | b);
  a >>= ctz(a);
  do {
    b >>= ctz(b);
    if (a > b) {
      LL t = b;
      b = a, a = t;
    }
    b -= a;
  } while (b);
  return a << t;
}
bool Miller_Rabin(LL x) {
  if (x == Prime[1] || x == Prime[0]) return 1;
  if (!(x % Prime[1]) || !(x % Prime[0])) return 0;
  if (Test(Prime[1], x) ^ 1) return 0;
  if (Test(Prime[0], x) ^ 1) return 0;
  if (x == Prime[2] || x == Prime[3]) return 1;
  if (!(x % Prime[2]) || !(x % Prime[3])) return 0;
  if (Test(Prime[2], x) ^ 1) return 0;
  if (Test(Prime[3], x) ^ 1) return 0;
  if (x == Prime[4] || x == Prime[5]) return 1;
  if (!(x % Prime[4]) || !(x % Prime[5])) return 0;
  if (Test(Prime[4], x) ^ 1) return 0;
  if (Test(Prime[5], x) ^ 1) return 0;
  if (x == Prime[6] || x == Prime[7]) return 1;
  if (!(x % Prime[6]) || !(x % Prime[7])) return 0;
  if (Test(Prime[6], x) ^ 1) return 0;
  if (Test(Prime[7], x) ^ 1) return 0;
  return 1;
}
LL Irand(LL x) {
  return 1ll * ((rand() << 15 ^ rand()) << 30 ^ (rand() << 15 ^ rand())) % x;
}
LL qwq(LL x) {
  LL C = Irand(x);
  LL t1 = Irand(x), t2 = guisuMul(t1, t1, x) + C;
  LL dif = t1 > t2 ? (t1 - t2) : (t2 - t1), G = gcd(x, dif);
  while (G == 1) {
    t1 = guisuMul(t1, t1, x) + C;
    if (t1 >= x) t1 %= x;
    t2 = guisuMul(t2, t2, x) + C, t2 = guisuMul(t2, t2, x) + C;
    if (t2 >= x) t2 %= x;
    dif = t1 > t2 ? (t1 - t2) : (t2 - t1), G = gcd(x, dif);
  }
  return G;
}
void Pollard_Rho(LL x) {
  if (x == 1) return;
  if (Miller_Rabin(x)) {
    Ans = max(Ans, x);
    return;
  }
  LL y = x;
  while (y == x) y = qwq(x);
  Pollard_Rho(y), Pollard_Rho(x / y);
}
int main() {
  srand(19260817);
  T = qr();
  while (T--) {
    N = qr(), Ans = -1, Pollard_Rho(N);
    if (Ans == N) puts("Prime");
    else printf("%lld", Ans), putchar('\n');
  }
}
