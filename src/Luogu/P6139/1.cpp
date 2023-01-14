#include <bits/stdc++.h>
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::str {
template <u32 SZ = 26, u32 BASE = u32('a')>
class orthodox_ex_suffix_automaton {
  struct YYZ {
    u32 len, link;
    std::array<u32, SZ> nex{};
  };

public:
  u32 sz;
  vec<YYZ> st;
  orthodox_ex_suffix_automaton(): sz(1) {
    st.push_back(YYZ()), st[0].len = 0, st[0].link = -1u;
  }
  u32 extend(u32 last, u32 c) {
    u32 cur = st[last].nex[c];
    if (st[cur].len) return cur;
    st[cur].len = st[last].len + 1;
    u32 p = st[last].link;
    while (p != -1u && !st[p].nex[c]) {
      st[p].nex[c] = cur;
      p = st[p].link;
    }
    if (p == -1u) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(YYZ());
        for (u32 i = 0; i < SZ; ++i)
          if (st[q].nex[i] && st[st[q].nex[i]].len)
            st[clone].nex[i] = st[q].nex[i];
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;
        while (p != -1u && st[p].nex[c] == q) {
          st[p].nex[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    return cur;
  }
  void insert(std::string s) {
    u32 u = 0;
    for (auto cc : s) {
      u32 c = cc - BASE;
      if (!st[u].nex[c]) st[u].nex[c] = sz++, st.push_back(YYZ());
      u = st[u].nex[c];
    }
  }
  void build() {
    std::queue<std::pair<u32, char>> q;
    for (u32 i = 0; i < SZ; ++i)
      if (st[0].nex[i]) q.push({0, i});
    while (q.size()) {
      auto [last, c] = q.front();
      q.pop();
      last = extend(last, c);
      for (u32 i = 0; i < SZ; ++i)
        if (st[last].nex[i]) q.push({last, i});
    }
  }
};
}  // namespace tifa_libs::str
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n;
  std::string s;
  std::cin >> n;
  tifa_libs::str::orthodox_ex_suffix_automaton sam;
  for (usz i = 0; i < n; ++i) std::cin >> s, sam.insert(s);
  sam.build();
  usz ans = 0;
  for (usz i = 1; i < sam.sz; ++i)
    ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n' << sam.sz;
  return 0;
}
