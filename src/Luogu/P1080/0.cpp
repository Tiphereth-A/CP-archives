#include <bits/stdc++.h>
#define N 1005
#define D 100000000
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define _rfor(i, l, r) for (int(i) = (l); (i) >= (r); --(i))
typedef long long ll;
typedef unsigned long long ull;
#define gi(a) do {
char ch;
while ((a = getchar()) > '9' || a < '0');
for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9';
     a = (a << 3) + (a << 1) + ch - '0');
}
while (0) struct node {
    int a, b;
    ll mul;
  } p[N];
struct bign {
#define M 5005
  ll num[M], len;
  bign() {
    memset(num, 0, sizeof(num));
    len = 1;
  }
} ans, final, c;
int n;
bool cmp(node a, node b) { return a.mul < b.mul; }
void mul(int m) {
  _for(i, 1, ans.len) ans.num[i] *= m;
  _for(i, 1, ans.len) {
    ll *tmp = ans.num + i;
    if (*tmp >= D) {
      *(tmp + 1) += *tmp / D;
      *tmp %= D;
    }
    if (i == ans.len && *(tmp + 1)) ++ans.len;
  }
}
void div(int d) {
  ull q = 0LL;
  memset(c.num, 0, sizeof(c.num));
  c.len = ans.len;
  _rfor(i, c.len, 1) {
    q *= D;
    q += ans.num[i];
    c.num[i] = q / d;
    q %= d;
  }
  while (c.len > 1 && !c.num[c.len]) --c.len;
}
bool comp() {
  if (c.len > final.len) return 1;
  if (c.len < final.len) return 0;
  _rfor(i, c.len, 1) {
    if (c.num[i] > final.num[i]) return 1;
    if (c.num[i] < final.num[i]) return 0;
  }
}
int main() {
  gi(n);
  _for(i, 0, n) {
    gi(p[i].a);
    gi(p[i].b);
    p[i].mul = p[i].a;
    p[i].mul *= p[i].b;
  }
  std::sort(p + 1, p + n + 1, cmp);
  ans.num[1] = 1;
  _for(i, 1, n) {
    mul(p[i - 1].a);
    div(p[i].b);
    if (comp()) {
      memset(final.num, 0, sizeof(final.num));
      final = c;
    }
  }
  printf("%d", final.num[final.len]);
  _rfor(i, final.len - 1, 1) printf("%08d", final.num[i]);
  return 0;
}
