#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
typedef long long i64;
const int N = 1e3 + 5;
int n, m, g[N][N];
struct point {
  int x, y;
  point(int _x = 0, int _y = 0): x(_x), y(_y) {}
  point operator+(const point &oth) { return point(x + oth.x, y + oth.y); }
};
const point d[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool judge(point p) {
  if (p.x > 1 && !(g[p.x][p.y] ^ g[p.x - 1][p.y])) return 1;
  if (p.x < n && !(g[p.x][p.y] ^ g[p.x + 1][p.y])) return 1;
  if (p.y > 1 && !(g[p.x][p.y] ^ g[p.x][p.y - 1])) return 1;
  if (p.y < m && !(g[p.x][p.y] ^ g[p.x][p.y + 1])) return 1;
  return 0;
}
bool legel(point p) { return p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m; }
bool extended[N][N];
i64 len_circ[N][N];
int main() {
  int t;
  cin >> n >> m >> t;
  string str;
  getline(cin, str);
  _for(i, 1, n) {
    getline(cin, str);
    _for(j, 1, m) g[i][j] = str[j - 1] - '0';
  }
  queue<point> q;
  _for(i, 1, n)
    _for(j, 1, m) {
      if (judge({i, j})) {
        q.push({i, j});
        extended[i][j] = 1;
        len_circ[i][j] = 0;
      }
    }
  if (q.empty()) {
    int u, v;
    i64 k;
    _for(i, 1, t) {
      cin >> u >> v >> k;
      cout << g[u][v] << endl;
    }
    return 0;
  }
  while (!q.empty()) {
    point now_p = q.front();
    q.pop();
    for (auto &_d : d) {
      point tmp_p = now_p + _d;
      if (legel(tmp_p) && !extended[tmp_p.x][tmp_p.y]) {
        q.push(tmp_p);
        extended[tmp_p.x][tmp_p.y] = 1;
        len_circ[tmp_p.x][tmp_p.y] = len_circ[now_p.x][now_p.y] + 1;
      }
    }
  }
  int u, v;
  i64 k;
  _for(i, 1, t) {
    cin >> u >> v >> k;
    cout << (k <= len_circ[u][v] ? g[u][v] :
                                   g[u][v] ^ ((k - len_circ[u][v]) & 1))
         << endl;
  }
  return 0;
}
