#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
const int N = 1e7 + 5;
int n, m;
int tr[N];
#define lowbit(x) (x) & (-(x))
void add(int s, int t) {
  for (int i = s; i <= n; i += lowbit(i)) ++tr[i];
  for (int i = t + 1; i <= n; i += lowbit(i)) --tr[i];
}
i64 query(int x) {
  i64 ans = 0;
  for (int i = x; i; i -= lowbit(i)) ans += tr[i];
  return ans;
}
int main() {
  read(n, m);
  int f, a, b;
  _for(i, 1, m) {
    read(f, a);
    if (f) printf("%lld\n", query(a));
    else {
      read(b);
      add(a, b);
    }
  }
  return 0;
}
