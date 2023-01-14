#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
#define pb push_back
int _w, _t;
FILE *_f;
const int MOD = 1e9 + 7;
int n, m, f[10][10], edge[2500][2500];
int plu(int u, int v) { return (u + v) % MOD; }
int mul(int u, int v) { return (int)(1LL * u * v % MOD); }
int qpow(int u, int v) {
  int tmp = 1;
  while (v > 0) {
    if (v & 1) { tmp = mul(tmp, u); }
    u = mul(u, u);
    v >>= 1;
  }
  return tmp;
}
int A(int u, int v) {
  int tmp = 1;
  for (int i = u, j = 1; j <= v; i--, j++) { tmp = mul(tmp, i); }
  return tmp;
}
vector<vi> ans[8][8];
bool check(vi va, vi vb, int u) {
  int tmp = 0;
  for (int i = 0; i < u; i++) { tmp += (va[i] == vb[i] ? 1 : 0); }
  if (tmp > 1) { return 0; }
  for (int i = 0; i < u; i++) {
    for (int j = i + 1; j < u; j++) {
      if (va[i] == va[j] && vb[i] == vb[j]) { return 0; }
    }
  }
  return 1;
}
vi trans3(int u, int v) {
  vi tmp(v);
  for (int i = 0; i < v; i++) {
    tmp[i] = u % 3;
    u /= 3;
  }
  return tmp;
}
void work(int u, int v) {
  int mx = qpow(3, u);
  for (auto p : ans[u][v - 1]) {
    int lst = p[v - 2];
    p.pb(0);
    for (int i = lst + 1, flag; i < mx; i++) {
      flag = 1;
      for (int j = 0; j < v - 1; j++) {
        if (!check(trans3(p[j], u), trans3(i, u), u)) { flag = 0; }
      }
      if (flag) {
        p[v - 1] = i;
        ans[u][v].pb(p);
      }
    }
  }
  f[u][v] = (int)ans[u][v].size();
  for (int i = 1; i <= v; i++) { f[u][v] = mul(f[u][v], i); }
}
void triprint(int u, int v) {
  printf("(");
  stack<int> tmp;
  for (int i = 0; i < v; i++) {
    tmp.push(u % 3);
    u /= 3;
  }
  for (int i = 0; i < v; i++) {
    printf("%d ", tmp.top());
    tmp.pop();
  }
  printf(")");
}
void pre(int u) {
  int mx = qpow(3, u);
  memset(edge, 0, sizeof edge);
  for (int i = 0; i < mx; i++) {
    vi bit[2];
    bit[0] = trans3(i, u);
    for (int j = i + 1; j < mx; j++) {
      bit[1] = trans3(j, u);
      if (!check(bit[0], bit[1], u)) { continue; }
      edge[i][j] = edge[j][i] = 1;
    }
  }
  vi tmp(1);
  for (int i = 0; i < mx; i++) {
    tmp[0] = i;
    ans[u][1].pb(tmp);
  }
  for (int i = 2, lst; i < u; i++) {
    for (auto v : ans[u][i - 1]) {
      lst = v[i - 2];
      for (int j = lst + 1, flag; j < mx; j++) {
        flag = 1;
        for (auto w : v) {
          if (!edge[w][j]) { flag = 0; }
        }
        if (flag) {
          vi pa = v;
          pa.pb(j);
          ans[u][i].pb(pa);
        }
      }
    }
  }
}
void init() {
  for (int i = 2; i < 8; i++) {
    f[2][i] = plu(mul(3 * i, A(6, i - 1)), A(6, i));
  }
  for (int i = 3; i < 8; i++) { pre(i); }
  for (int i = 3; i < 8; i++) {
    printf("f[%d][%d]=%d\n", i, i - 1, (int)ans[i][i - 1].size());
    for (int j = i; j < 8; j++) { work(i, j); }
  }
  for (int i = 1; i < 8; i++) {
    for (int j = 1; j < 8; j++) { printf("%d%c", f[i][j], " \n"[j == 7]); }
  }
}
void solve() {
  scanf("%d%d", &n, &m);
  if (n > m) { swap(n, m); }
  if (n == 1) {
    printf("0\n");
    return;
  }
  if (m > 7) {
    printf("%d\n", qpow(3, n * m));
    return;
  } else {
    printf("%d\n", plu(qpow(3, n * m), MOD - f[n][m]));
  }
}
void newinit() {
  f[2][2] = 66;
  f[2][3] = 390;
  f[2][4] = 1800;
  f[2][5] = 6120;
  f[2][6] = 13680;
  f[2][7] = 15120;
  f[3][3] = 3198;
  f[3][4] = 13176;
  f[3][5] = 27000;
  f[3][6] = 13680;
  f[3][7] = 15120;
  f[4][4] = 24336;
  f[4][5] = 4320;
  f[5][5] = 4320;
}
int main() {
  newinit();
  _w = scanf("%d", &_t);
  while (_t--) solve();
  return 0;
}
