#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5, B = 987654, mo = 1e6 + 3;
void red(int &x) { x += x >> 31 & mo; }
int mi[6];
typedef unsigned long long ull;
int x[6], x2[6], n, k, i, j, l, dv[6];
ull seed, xs[N];
struct P {
  int a[6];
  void ini() {
    for (int i = 0; i < k; ++i) cin >> a[i], a[i] += 1e7;
  }
} a[N];
double xx[6];
ull dis(int p, int q) {
  ull z = 0;
  for (int i = 0; i < k; ++i) z += 1ll * a[p].a[i] * a[q].a[i];
  return xs[p] + xs[q] - z * 2;
}
double R, iR;
ull rR;
bool bb;
struct hmp {
  int h[mo], nxt[N];
  int geth(int *x) {
    int v = 0;
    for (int j = 0; j < k; ++j) v = (1ll * v * B + x[j]) % mo;
    return v;
  }
  void ins(int i, int *x) {
    int v = geth(x);
    nxt[i] = h[v];
    h[v] = i;
  }
} mp;
void getv(int i) {
  for (int j = 0; j < k; ++j) x[j] = xx[j] = a[i].a[j] * iR + 1e-12;
}
void build(int l) {
  memset(mp.h, 0, sizeof mp.h);
  for (int i = 1; i <= l; ++i) getv(i), mp.ins(i, x);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  k = 2;
  for (i = 1; i <= n; ++i) a[i].ini();
  for (i = 1; i <= n; ++i)
    for (j = 0; j < k; ++j) xs[i] += 1ll * a[i].a[j] * a[i].a[j];
  for (i = *mi = 1; i < k; ++i) mi[i] = 1ll * mi[i - 1] * B % mo;
  rR = dis(1, 2);
  R = sqrt(rR) * 2;
  iR = 1.0 / R;
  build(2);
  for (i = 3; i <= n; ++i) {
    bb = 0;
    getv(i);
    for (j = 0; j < k; ++j)
      dv[j] = xx[j] < x[j] + 0.5 ? mo - mi[k - 1 - j] : mi[k - 1 - j];
    static int ha[99];
    ha[0] = mp.geth(x);
    for (j = 0; j < k; ++j)
      for (l = 0; l < 1 << j; ++l) red(ha[l | (1 << j)] = ha[l] + dv[j] - mo);
    for (j = 0; j < 4; ++j)
      for (l = mp.h[ha[j]]; l; l = mp.nxt[l]) {
        ull nd = dis(i, l);
        if (nd < rR) rR = nd, bb = 1;
      }
    if (bb) R = sqrt(rR) * 2, iR = 1.0 / R, build(i);
    else mp.ins(i, x);
  }
  cout << rR << endl;
}
