#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define rfor_(i, r, l, vars...)                                           \
  for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; \
       i >= i##end;                                                       \
       --i)
const int N = 31, M = 114514;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
int dis[N], cnt[N];
void dijkstra(int s) {
  priority_queue<pair<int, int>,
                 vector<pair<int, int>>,
                 greater<pair<int, int>>>
    q;
  memset(dis, 0x3f, sizeof(dis));
  memset(cnt, 0, sizeof(cnt));
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (dis[now] < dis_now) continue;
    for (int i = head[now], to; ~i; i = e[i].next)
      if ((dis[to = e[i].to] > dis[now] + e[i].w) ||
          (dis[to = e[i].to] == dis[now] + e[i].w && cnt[to] < cnt[now] + 1)) {
        q.emplace(dis[to] = dis[now] + e[i].w, to);
        cnt[to] = cnt[now] + 1;
      }
  }
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string s;
  cin >> s;
  cnt_edge = 0;
  memset(head, 0xff, sizeof head);
  bitset<N> vis;
  vector<vector<int>> ss(31);
  for (char ch : s) vis.set(ch - 'a');
  for_(i, 0, s.size() - 1) ss[s[i] - 'a'].push_back(i);
  for (int i = 0; i < 26; ++i)
    for (int j = i + 1; j < 26; ++j)
      if (vis[i] && vis[j]) {
        addEdge(i, j, j - i);
        addEdge(j, i, j - i);
      }
  dijkstra(s.front() - 'a');
  int _ = cnt[s.back() - 'a'];
  stack<int> ans;
  rfor_(j, ss[s.back() - 'a'].size() - 1, 0)
    ans.push(ss[s.back() - 'a'][j] + 1);
  while (~_) {
    --_;
    for (int i = 0; i < 26; ++i) {
      if (cnt[i] == _ && dis[i] + abs(s[ans.top() - 1] - 'a' - i) ==
                           dis[s[ans.top() - 1] - 'a']) {
        rfor_(j, ss[i].size() - 1, 0) ans.push(ss[i][j] + 1);
        break;
      }
    }
  }
  cout << dis[s.back() - 'a'] << ' ' << ans.size() << '\n';
  while (!ans.empty()) {
    cout << ans.top();
    ans.pop();
    cout << " \n"[ans.empty()];
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
