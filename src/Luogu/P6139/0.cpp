#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::str {
template <u32 SZ = 26>
class ex_suffix_automaton {
  struct YYZ {
    u32 len, link;
    std::array<u32, SZ> nex{};
  };

public:
  u32 sz;
  vec<YYZ> st;
  ex_suffix_automaton(): sz(1), st(1) { st[0].len = 0, st[0].link = -1; }
  u32 extend(u32 last, u32 c) {
    if (st[last].nex[c]) {
      u32 p = last, q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) return q;
      else {
        u32 clone = sz++;
        st.push_back(YYZ());
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;
        st[clone].nex = st[q].nex;
        while (p != -1u && st[p].nex[c] == q)
          st[p].nex[c] = clone, p = st[p].link;
        st[q].link = clone;
        return clone;
      }
    }
    u32 cur = sz++, p = last;
    st.push_back(YYZ());
    st[cur].len = st[last].len + 1;
    while (p != -1u && !st[p].nex[c]) st[p].nex[c] = cur, p = st[p].link;
    if (p == -1u) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(YYZ());
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;
        st[clone].nex = st[q].nex;
        while (p != -1u && st[p].nex[c] == q)
          st[p].nex[c] = clone, p = st[p].link;
        st[q].link = st[cur].link = clone;
      }
    }
    return cur;
  }
};
}  // namespace tifa_libs::str
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::string s;
  std::cin >> n;
  tifa_libs::str::ex_suffix_automaton sam;
  for (u32 i = 0; i < n; ++i) {
    std::cin >> s;
    u32 last = 0;
    for (auto c : s) last = sam.extend(last, u32(c - 'a'));
  }
  u64 ans = 0;
  for (u32 i = 1; i < sam.sz; ++i)
    ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n' << sam.sz;
  return 0;
}
