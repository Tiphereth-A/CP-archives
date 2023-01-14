#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define memn(a) memset(a, -1, sizeof(a))
typedef long long ll;
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
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
const int M = 5000005;
struct pnt {
  int dis, val;
} a[M];
int n, d, k, ans = -1;
ll sum;
ll dp(int left, int right) {
  int f[M], dq[M];
  mem(dq);
  memn(f);
  f[0] = 0;
  int head = 1, tail = 0, i = 0;
  _for(j, 1, n) {
    while (a[j].dis - a[i].dis >= left && i < j) {
      if (f[i] != -1) {
        while (head <= tail && f[dq[tail]] <= f[i]) --tail;
        dq[++tail] = i;
      }
      ++i;
    }
    while (head <= tail && a[j].dis - a[dq[head]].dis > right) ++head;
    if (head <= tail) f[j] = f[dq[head]] + a[j].val;
  }
  ll num = 0;
  _for(i, 1, n)
    if (num < f[i]) num = f[i];
  return num;
}
int main() {
  read(n, d, k);
  _for(i, 1, n) {
    read(a[i].dis, a[i].val);
    if (a[i].val > 0) sum += a[i].val;
  }
  int left = 0, right = a[n].dis;
  if (sum < k) {
    printf("-1\n");
    return 0;
  }
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    int f = Max(1, d - mid), l = d + mid;
    ll num = dp(f, l);
    if (num < k) left = mid + 1;
    else {
      ans = mid;
      right = mid - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
