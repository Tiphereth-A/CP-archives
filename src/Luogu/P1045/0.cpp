#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
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
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
void read(A &a, B &b, C &c, D &d) {
  read(a), read(b), read(c), read(d);
}
template <typename A>
void write(A &x) {
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
  return;
}
const int M = 100005;
struct bign {
  int n[M];
  bign() { memset(n, 0, sizeof(n)); }
  void print() {
    for (int i = n[0], j = 1; i >= 1; i--, j++) {
      if (j > 50) {
        putchar('\n');
        j = 1;
      }
      putchar(n[i] + '0');
    }
    puts("");
  }
  bign operator=(const bign a) {
    memset(n, 0, sizeof(n));
    _for(i, 0, a.n[0]) n[i] = a.n[i];
    return *this;
  }
  bign operator*(const bign a) const {
    bign c;
    c.n[0] = a.n[0] + n[0];
    if (c.n[0] > 500) c.n[0] = 500;
    _for(i, 1, a.n[0])
      _for(j, 1, n[0]) {
        c.n[i + j - 1] += a.n[i] * n[j];
        if (c.n[i + j - 1] > 9) {
          c.n[i + j] += c.n[i + j - 1] / 10;
          c.n[i + j - 1] %= 10;
        }
      }
    return c;
  }
};
int main() {
  int n;
  scanf("%d", &n);
  struct bign a, tmp;
  a.n[0] = a.n[1] = tmp.n[0] = 1;
  tmp.n[1] = 2;
  printf("%d\n", (int)(0.30103 * n + 1));
  for (; n; n >>= 1, tmp = tmp * tmp)
    if (n & 1) a = a * tmp;
  a.n[1]--;
  a.n[0] = 500;
  a.print();
  return 0;
}
