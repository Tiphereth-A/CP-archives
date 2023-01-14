#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const int OFFSET = 5;
const int N = 1e3 + OFFSET, M = 2e3 + OFFSET, K = 21;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int in[N], out[N];
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
  ++in[y];
  ++out[x];
}
bool find(int x, int y) {
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].to == y) return 1;
  return 0;
}
int seq[N], cnt_seq;
int topo(int n) {
  queue<int> q;
  _for(i, 1, n)
    if (!in[i]) q.push(i);
  bool flag = 0;
  while (!q.empty()) {
    if (q.size() > 1) flag = 1;
    int now = q.front();
    q.pop();
    seq[++cnt_seq] = now;
    for (int i = head[now], to; i; i = e[i].next)
      if (!(--in[to = e[i].to])) q.push(to);
  }
  if (cnt_seq < n) return 0;
  if (flag) return 1;
  return 2;
}
int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    if (n == 0 && m == 0) break;
    char c1, op, c2;
    bool _cont = 0;
    int x, y;
    int flag = 1;
    int stop_pos = 0;
    _for(i, 1, m) {
      scanf(" %c%c%c", &c1, &op, &c2);
      if (_cont) continue;
      if (op == '>') swap(c1, c2);
      x = c1 - 'A' + 1;
      y = c2 - 'A' + 1;
      if (!find(x, y)) addEdge(x, y);
      memcpy(out, in, sizeof(out));
      cnt_seq = 0;
      if ((flag = topo(n)) != 1) {
        _cont = 1;
        stop_pos = i;
      }
      memcpy(in, out, sizeof(in));
    }
    switch (flag) {
      case 0:
        printf("Inconsistency found after %d relations.\n", stop_pos);
        break;
      case 1: puts("Sorted sequence cannot be determined."); break;
      case 2:
        printf("Sorted sequence determined after %d relations: ", stop_pos);
        _for(i, 1, cnt_seq) putchar(seq[i] + 'A' - 1);
        puts(".");
        break;
    }
    _set_nul_n(head, n + 1);
    _set_nul_n(in, n + 1);
    _set_nul_n(out, n + 1);
    cnt_edge = cnt_seq = 0;
  }
  return 0;
}
