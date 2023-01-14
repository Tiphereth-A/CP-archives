#include <bits/stdc++.h>
const int N = 8e4 + 5;
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C, typename D, typename E>
void read(A &a, B &b, C &c, D &d, E &e) {
  read(a), read(b), read(c), read(d), read(e);
}
int n, opt, mod, min, max;
i64 b[N], s[N];
int l, r, k;
i64 now, ans;
char op[15];
int main() {
  read(n, opt, mod, min, max);
  for (int i = 1; i <= opt; ++i) {
    scanf("%s", op);
    read(l, r);
    if (*op == 'A') {
      read(k);
      b[l] += k;
      b[r + 1] -= k;
    } else {
      now = ans = 0;
      for (int j = 1; j < l; ++j) now += b[j];
      for (int j = l; j <= r; ++j) {
        now += b[j];
        i64 tmp = (now * j) % mod;
        if (tmp >= min && tmp <= max) ++ans;
      }
      printf("%lld\n", ans);
    }
  }
  read(k);
  now = 0;
  for (int i = 1; i <= n; ++i) {
    now += b[i];
    i64 tmp = (now * i) % mod;
    s[i] = (tmp >= min && tmp <= max) ? s[i - 1] + 1 : s[i - 1];
  }
  for (int i = 1; i <= k; ++i) {
    read(l, r);
    printf("%lld\n", s[r] - s[l - 1]);
  }
  return 0;
}
