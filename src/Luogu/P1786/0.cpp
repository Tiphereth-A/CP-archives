#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
std::map<std::string, u32> mp{{"BangZhu", 0},
                              {"FuBangZhu", 1},
                              {"HuFa", 2},
                              {"ZhangLao", 3},
                              {"TangZhu", 4},
                              {"JingYing", 5},
                              {"BangZhong", 6}};
struct node {
  std::string name, past_title, now_title;
  u64 tribute;
  u32 level, id;
};
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  std::vector<node> ab(n + 1);
  for (u32 i = 1; i <= n; ++i) {
    std::cin >> ab[i].name >> ab[i].past_title >> ab[i].tribute >> ab[i].level;
    ab[i].id = i;
  }
  std::sort(ab.begin() + 4, ab.end(), [](node const &x, node const &y) {
    return x.tribute == y.tribute ? x.id < y.id : x.tribute > y.tribute;
  });
  for (u32 i = 1; i <= n; ++i) {
    if (i == 1) ab[i].now_title = "BangZhu";
    else if (i <= 3) ab[i].now_title = "FuBangZhu";
    else if (i <= 5) ab[i].now_title = "HuFa";
    else if (i <= 9) ab[i].now_title = "ZhangLao";
    else if (i <= 16) ab[i].now_title = "TangZhu";
    else if (i <= 41) ab[i].now_title = "JingYing";
    else ab[i].now_title = "BangZhong";
  }
  std::sort(ab.begin() + 1, ab.end(), [](node const &x, node const &y) {
    return mp[x.now_title] == mp[y.now_title] ?
             x.level == y.level ? x.id < y.id : x.level > y.level :
             mp[x.now_title] < mp[y.now_title];
  });
  for (u32 i = 1; i <= n; ++i)
    std::cout << ab[i].name << " " << ab[i].now_title << " " << ab[i].level
              << '\n';
  return 0;
}
