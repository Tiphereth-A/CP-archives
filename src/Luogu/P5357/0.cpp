#include <bits/stdc++.h>
using u32 = uint32_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::str {
template <u32 SZ = 26, u32 BASE = u32('a')>
class aho_corasick_automaton {
  struct YYZ {
    std::array<u32, SZ> nex{};
    u32 fail, tot;
    vec<u32> end;
  };

public:
  vec<YYZ> t;
  u32 sz;
  aho_corasick_automaton(): t(1), sz(1) {}
  void insert(std::string s, u32 id = -1u) {
    u32 u = 0;
    ++t[u].tot;
    for (auto c : s) {
      u32 a = u32(c) - BASE;
      if (!t[u].nex[a]) t[u].nex[a] = sz++, t.push_back(YYZ());
      u = t[u].nex[a], ++t[u].tot;
    }
    if (id != -1u) t[u].end.push_back(id);
  }
  void getfail() {
    std::queue<u32> q;
    for (u32 i = 0; i < SZ; ++i)
      if (t[0].nex[i]) q.push(t[0].nex[i]);
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (u32 i = 0; i < SZ; ++i) {
        if (t[u].nex[i])
          t[t[u].nex[i]].fail = t[t[u].fail].nex[i], q.push(t[u].nex[i]);
        else t[u].nex[i] = t[t[u].fail].nex[i];
      }
    }
  }
  void build(vec<std::string> s_) {
    for (u32 i = 0; i < s_.size(); ++i) insert(s_[i], i);
    getfail();
  }
};
}  // namespace tifa_libs::str
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::string s;
  std::cin >> n;
  vec<u32> ans(n);
  tifa_libs::str::aho_corasick_automaton acam;
  for (u32 i = 0; i < n; ++i) std::cin >> s, acam.insert(s, i);
  acam.getfail();
  std::cin >> s;
  vec<u32> sz(acam.sz), in(acam.sz);
  for (u32 i = 0, u = 0; i < s.size(); ++i)
    u = acam.t[u].nex[u32(s[i] - 'a')], sz[u] += 1;
  for (u32 i = 0; i < acam.sz; ++i) ++in[acam.t[i].fail];
  std::queue<u32> q;
  for (u32 i = 0; i < acam.sz; ++i)
    if (!in[i]) q.push(i);
  while (!q.empty()) {
    u32 u = q.front();
    q.pop();
    for (auto x : acam.t[u].end) ans[x] = sz[u];
    u32 v = acam.t[u].fail;
    sz[v] += sz[u];
    --in[v];
    if (!in[v]) q.push(v);
  }
  for (auto x : ans) std::cout << x << '\n';
  return 0;
}
