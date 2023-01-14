#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
int t[N << 2][4], tag[N << 2][4];
void update(int v) {
  for (int i = 0; i < 4; ++i) {
    t[v][i] = max(t[v][i], max(t[v << 1][i], t[v << 1 | 1][i]));
  }
}
void pushdown(int v) {
  for (int i = 0; i < 4; ++i) {
    if (tag[v][i]) {
      t[v << 1][i] += tag[v][i];
      t[v << 1 | 1][i] += tag[v][i];
      tag[v << 1][i] += tag[v][i];
      tag[v << 1 | 1][i] += tag[v][i];
      tag[v][i] = 0;
    }
  }
}
void add(int v, int l, int r, int x, int y, int a2, int a3, int a5, int a7) {
  if (x <= l && r <= y) {
    if (a2) {
      tag[v][0] += a2;
      t[v][0] += a2;
    }
    if (a3) {
      tag[v][1] += a3;
      t[v][1] += a3;
    }
    if (a5) {
      tag[v][2] += a5;
      t[v][2] += a5;
    }
    if (a7) {
      tag[v][3] += a7;
      t[v][3] += a7;
    }
    return;
  }
  int mid = l + r >> 1;
  pushdown(v);
  if (x <= mid) add(v << 1, l, mid, x, y, a2, a3, a5, a7);
  if (mid < y) add(v << 1 | 1, mid + 1, r, x, y, a2, a3, a5, a7);
  update(v);
  return;
}
int query(int v, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    int mx = 0;
    for (int i = 0; i < 4; ++i) { mx = max(mx, t[v][i]); }
    return mx;
  }
  int mid = l + r >> 1, res = 0;
  pushdown(v);
  if (x <= mid) res = max(res, query(v << 1, l, mid, x, y));
  if (mid < y) res = max(res, query(v << 1 | 1, mid + 1, r, x, y));
  update(v);
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    string op;
    int l, r, x;
    cin >> op >> l >> r;
    if (op == "MULTIPLY") {
      cin >> x;
      if (x == 2) {
        add(1, 1, n, l, r, 1, 0, 0, 0);
      } else if (x == 3) {
        add(1, 1, n, l, r, 0, 1, 0, 0);
      } else if (x == 4) {
        add(1, 1, n, l, r, 2, 0, 0, 0);
      } else if (x == 5) {
        add(1, 1, n, l, r, 0, 0, 1, 0);
      } else if (x == 6) {
        add(1, 1, n, l, r, 1, 1, 0, 0);
      } else if (x == 7) {
        add(1, 1, n, l, r, 0, 0, 0, 1);
      } else if (x == 8) {
        add(1, 1, n, l, r, 3, 0, 0, 0);
      } else if (x == 9) {
        add(1, 1, n, l, r, 0, 2, 0, 0);
      } else if (x == 10) {
        add(1, 1, n, l, r, 1, 0, 1, 0);
      }
    } else {
      cout << "ANSWER " << query(1, 1, n, l, r) << "\n";
    }
  }
  return 0;
}
