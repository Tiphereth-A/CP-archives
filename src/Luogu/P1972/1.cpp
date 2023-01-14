#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define N 500005
#define gi(a)                                            \
  do {                                                   \
    char ch;                                             \
    while ((a = getchar()) > '9' || a < '0');            \
    for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; \
         a = (a << 3) + (a << 1) + ch - '0');            \
  } while (0)
int Max(int x, int y) {
  int m = (x - y) >> 31;
  return (y & m | x & ~m);
}
struct data {
  int l, r, id, ans;
} q[200005];
bool cmp1(data a, data b) { return a.l == b.l ? a.r < b.r : a.l < b.l; }
bool cmp2(data a, data b) { return a.id < b.id; }
int a[N], t[N], nex[N], num[1000005], n;
void insert(int x, int f) {
  for (int i = x; i <= n; i += lowbit(i)) t[i] += f;
}
int query(int x) {
  int ans = 0;
  for (int i = x; i; i -= lowbit(i)) ans += t[i];
  return ans;
}
int main() {
  gi(n);
  int mx;
  for (int i = 1; i <= n; ++i) {
    gi(a[i]);
    mx = Max(mx, a[i]);
  }
  for (int i = n; i > 0; --i) {
    int tmp = a[i];
    nex[i] = num[tmp];
    num[tmp] = i;
  }
  for (int i = 0; i <= mx; ++i) {
    int tmp = num[i];
    if (tmp) insert(tmp, 1);
  }
  int m;
  gi(m);
  for (int i = 1; i <= m; ++i) {
    data *tmp = &q[i];
    gi((*tmp).l);
    gi((*tmp).r);
    (*tmp).id = i;
  }
  std::sort(q + 1, q + m + 1, cmp1);
  int l = 1;
  for (int i = 1; i <= m; ++i) {
    data *t1 = &q[i];
    while (l < (*t1).l) {
      int t2 = nex[l];
      if (t2) insert(t2, 1);
      ++l;
    }
    (*t1).ans = query((*t1).r) - query((*t1).l - 1);
  }
  std::sort(q + 1, q + m + 1, cmp2);
  for (int i = 1; i <= m; ++i) printf("%d\n", q[i].ans);
  return 0;
}
