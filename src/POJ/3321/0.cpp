#include <cstdio>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
bool empty[N];
int start[N], end[N];
int size[N];
void dfs(int now, int f, int &cnt) {
  start[now] = ++cnt;
  size[now] = 1;
  for (int i = head[now], to; i; i = e[i].next) {
    dfs(to = e[i].to, now, cnt);
    size[now] += size[to];
  }
  end[now] = cnt;
}
class BIT {
private:
  int tree[N * 2];
  size_t lowbit(int x) { return x & (-x); }

public:
  BIT() {}
  void modify(size_t pos, int val = 1) {
    for (size_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  int query(size_t pos) {
    int ret = 0;
    for (size_t i = pos; i; i = (int)i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT tr;
int main() {
  int n;
  scanf("%d", &n);
  int x, y;
  _for(i, 1, n - 1) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }
  dfs(1, 0, x = 0);
  int m;
  scanf("%d", &m);
  char op = 0;
  _for(i, 1, m) {
    scanf(" %c%d", &op, &x);
    if (op == 'C') {
      empty[x] ^= 1;
      tr.modify(start[x], empty[x] ? -1 : 1);
    } else
      printf("%d\n", size[x] + (tr.query(end[x]) - tr.query(start[x] - 1)));
  }
  return 0;
}
