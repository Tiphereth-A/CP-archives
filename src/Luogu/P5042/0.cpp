#include <bits/stdc++.h>
using namespace std;
namespace Subtask_1 {
void main() {
  vector<bool> vb;
  vb.reserve(1 << 22);
  vb.push_back(false);
  for (int i = 0; i < 22; ++i)
    for (auto it = vb.begin(); it != vb.begin() + (1 << i); ++it)
      vb.push_back(!*it);
  for (auto i : vb) cout << (i ? '1' : '0');
  cout << '\n';
}
}  // namespace Subtask_1
namespace Subtask_2 {
void main() {
  string a("0"), b("1"), c;
  for (int i = 1; i < 33; ++i) {
    c = a + b;
    a = b;
    b = c;
  }
  cout << a << '\n';
}
}  // namespace Subtask_2
namespace Subtask_3 {
const int n = 12;
const int m = 177147;
int node[m + 1];
stack<int> s;
void f(int v) {
  int w;
  while (node[v] < 3) {
    s.push(w = 3 * v + node[v]++);
    v = w % m;
  }
}
void main() {
  string ans;
  f(0);
  int w;
  while (!s.empty()) {
    w = s.top();
    s.pop();
    ans.push_back(w % 3 + '0');
    f(w / 3);
  }
  ans += string(n - 1, '0');
  reverse(ans.begin(), ans.end());
  cout << ans << '\n';
}
}  // namespace Subtask_3
namespace Subtask_4 {
const int p = 104857601, n = 131072, n2 = n * 2;
int inv[n2 + 1];
void main() {
  inv[1] = 1;
  for (int i = 2; i <= n2; ++i) inv[i] = (int64_t)(p - p / i) * inv[p % i] % p;
  vector<int> v;
  v.reserve(n + 1);
  v.push_back(1);
  for (int i = 1; i <= n; ++i)
    v.push_back(1ll * v.back() * (n2 - i + 1) % p * inv[i] % p);
  cout << n2 << '\n';
  for (auto i : v) cout << i << '\n';
  for (auto it = v.rbegin() + 1; it != v.rend(); ++it) cout << *it << '\n';
}
}  // namespace Subtask_4
namespace Subtask_5 {
const int p = 104857601, n = 131072, n2 = n * 2;
int inv[n2 + 1];
void main() {
  inv[1] = 1;
  for (int i = 2; i <= n2; ++i) inv[i] = (int64_t)(p - p / i) * inv[p % i] % p;
  vector<int> v;
  v.reserve(n + 1);
  v.push_back(1);
  for (int i = 1; i <= n; ++i)
    v.push_back(1ll * v.back() * (n - i + 1) % p * inv[i] % p);
  cout << n << '\n';
  for (int i = 0; i <= n; ++i) cout << (i % 2 ? p - v[i] : v[i]) << '\n';
}
}  // namespace Subtask_5
namespace Subtask_6 {
const int p = 104857601, a = 23333333, b = 33333333;
constexpr int64_t qpow(int64_t a, int64_t b) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= p)
    if (b & 1) (res *= a) %= p;
  return res;
}
const int inv_a = qpow(a, p - 2);
const int n = 177147;
int inv[n + 1];
void main() {
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) inv[i] = (int64_t)(p - p / i) * inv[p % i] % p;
  int64_t res = qpow(a, n);
  cout << n << '\n' << res << '\n';
  for (int i = 1; i <= n; ++i)
    cout << (res = res * inv_a % p * b % p * (n - i + 1) % p * inv[i] % p)
         << '\n';
}
}  // namespace Subtask_6
namespace Subtask_7 {
const int n = 100000, m = 100000, q = 200000;
int dsu[n + 1];
int find(int x) { return x == dsu[x] ? dsu[x] : dsu[x] = find(dsu[x]); }
void merge(int x, int y) { dsu[find(x)] = find(y); }
void main() {
  for (int i = 1; i <= n; ++i) dsu[i] = i;
  for (int i = 0, x, y; i < m; ++i) {
    cin >> x >> y;
    merge(x, y);
  }
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y;
    cout << (find(x) == find(y) ? "0\n" : "2139062143\n");
  }
}
}  // namespace Subtask_7
namespace Subtask_8 {
const int n = 100000, m = 99999, q = 200000;
const int lbn = log2(n);
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[2 * m + 1];
int head[n + 1], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int acstr[n + 1][lbn + 1], max_w[n + 1][lbn + 1], dep[n + 1];
void multiply(int now, int fa) {
  dep[now] = dep[acstr[now][0] = fa] + 1;
  for (int i = 0; i < lbn; ++i) {
    acstr[now][i + 1] = acstr[acstr[now][i]][i];
    max_w[now][i + 1] = max(max_w[now][i], max_w[acstr[now][i]][i]);
  }
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    max_w[to][0] = e[i].w;
    multiply(to, now);
  }
}
int get_res(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int ans = 0;
  for (int i = lbn; ~i; --i)
    if (dep[acstr[x][i]] >= dep[y]) {
      ans = max(ans, max_w[x][i]);
      x = acstr[x][i];
    }
  if (x == y) return ans;
  for (int i = lbn; ~i; --i)
    if (acstr[x][i] != acstr[y][i]) {
      ans = max(ans, max(max_w[x][i], max_w[y][i]));
      x = acstr[x][i];
      y = acstr[y][i];
    }
  return max(ans, max(max_w[x][0], max_w[y][0]));
}
void main() {
  for (int i = 0, x, y, w; i < m; ++i) {
    cin >> x >> y >> w;
    addEdge(x, y, w);
    addEdge(y, x, w);
  }
  multiply(1, 0);
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y;
    cout << get_res(x, y) << '\n';
  }
}
#undef _for_graph
}  // namespace Subtask_8
namespace Subtask_9 {
const int n = 50000, m = 100000, q = 200000;
const int lbn = log2(n);
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[2 * m + 1];
int head[n + 1], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int dsu[n + 1];
int find(int x) { return x == dsu[x] ? dsu[x] : dsu[x] = find(dsu[x]); }
void merge(int x, int y) { dsu[find(x)] = find(y); }
int acstr[n + 1][lbn + 1], max_w[n + 1][lbn + 1], dep[n + 1];
void multiply(int now, int fa) {
  dep[now] = dep[acstr[now][0] = fa] + 1;
  for (int i = 0; i < lbn; ++i) {
    acstr[now][i + 1] = acstr[acstr[now][i]][i];
    max_w[now][i + 1] = max(max_w[now][i], max_w[acstr[now][i]][i]);
  }
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    max_w[to][0] = e[i].w;
    multiply(to, now);
  }
}
int get_res(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int ans = 0;
  for (int i = lbn; ~i; --i)
    if (dep[acstr[x][i]] >= dep[y]) {
      ans = max(ans, max_w[x][i]);
      x = acstr[x][i];
    }
  if (x == y) return ans;
  for (int i = lbn; ~i; --i)
    if (acstr[x][i] != acstr[y][i]) {
      ans = max(ans, max(max_w[x][i], max_w[y][i]));
      x = acstr[x][i];
      y = acstr[y][i];
    }
  return max(ans, max(max_w[x][0], max_w[y][0]));
}
struct Node {
  int x, y, w;
  bool operator<(const Node &rhs) const { return w < rhs.w; }
} data[m];
void main() {
  for (int i = 1; i <= n; ++i) dsu[i] = i;
  for (int i = 0; i < m; ++i) cin >> data[i].x >> data[i].y >> data[i].w;
  sort(data, data + m);
  for (int i = 0; i < m; ++i)
    if (find(data[i].x) != find(data[i].y)) {
      merge(data[i].x, data[i].y);
      addEdge(data[i].x, data[i].y, data[i].w);
      addEdge(data[i].y, data[i].x, data[i].w);
    }
  for (int i = 1; i <= n; ++i)
    if (!dep[i]) multiply(i, 0);
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y;
    if (find(x) != find(y)) {
      cout << "2139062143\n";
      continue;
    }
    cout << get_res(x, y) << '\n';
  }
}
#undef _for_graph
}  // namespace Subtask_9
namespace Subtask_10 {
void main() {
  cout << "Your program should output itself here.\n"
          "Sounds very difficult, yeah?\n"
          "Anyway, good luck!\n";
}
}  // namespace Subtask_10
#define _run_return(expressions) return (expressions), 0
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  string _;
  getline(cin, _);
  if (_.front() == 'M') _run_return(Subtask_10::main());
  if (_ == "22") _run_return(Subtask_1::main());
  if (_ == "33") _run_return(Subtask_2::main());
  if (_ == "12") _run_return(Subtask_3::main());
  if (_ == "131072") _run_return(Subtask_4::main());
  if (_ == "262144") _run_return(Subtask_5::main());
  if (_ == "531441") _run_return(Subtask_6::main());
  if (_ == "100000 100000 200000") _run_return(Subtask_7::main());
  if (_ == "100000 99999 200000") _run_return(Subtask_8::main());
  if (_ == "50000 100000 200000") _run_return(Subtask_9::main());
  return 1;
}
