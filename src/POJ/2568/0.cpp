#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;
const int N = 505;
struct Edge {
  int to, next;
} e[N];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = {y, head[x]};
  head[x] = cnt_edge;
}
int prufer[N], cnt[N];
bool vis[N];
void print(int fa, int now) {
  printf("(%d", now);
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    putchar(' ');
    print(now, to);
  }
  putchar(')');
}
int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss;
    memset(prufer, 0, sizeof(prufer));
    memset(vis, 0, sizeof(vis));
    memset(head, 0, sizeof(head));
    memset(cnt, 0, sizeof(cnt));
    cnt_edge = 0;
    int n = 0, _;
    ss << line;
    while (ss >> _) ++cnt[prufer[++n] = _];
    ++n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i)
      if (!cnt[i]) pq.push(i);
    for (int i = 1; i < n; ++i) {
      int now = pq.top();
      pq.pop();
      addEdge(prufer[i], now);
      addEdge(now, prufer[i]);
      if (!(--cnt[prufer[i]])) pq.push(prufer[i]);
    }
    if (n == 1) {
      puts("(1)");
      continue;
    }
    print(0, prufer[n - 1]);
    puts("");
  }
}
