#include <bits/stdc++.h>
using namespace std;
const auto _ = [](int x) -> uint8_t { return (1 << (x - 1)); };
const valarray<uint8_t> oper{_(1),
                             _(2),
                             _(3),
                             _(4),
                             _(5),
                             _(6),
                             _(7),
                             _(8),
                             _(1) | _(2),
                             _(2) | _(3),
                             _(3) | _(4),
                             _(5) | _(6),
                             _(6) | _(7),
                             _(7) | _(8)};
const valarray<uint8_t> gg = oper ^ ((1 << 8) - 1);
int sg(uint8_t state) {
  if (any_of(
        gg.begin(), gg.end(), [&](auto &&x) -> bool { return x == state; }))
    return 0;
  vector<int> rets;
  for (auto x : oper) {
    if (state & x) continue;
    rets.push_back(sg(state | x));
  }
  sort(rets.begin(), rets.end());
  if (rets.front()) return 0;
  for (auto it = rets.begin() + 1; it != rets.end(); ++it)
    if (*it - *(it - 1) > 1) return *(it - 1) + 1;
  return rets.back() + 1;
}
const initializer_list<uint8_t> states = {_(1), _(1) | _(2), _(2), _(2) | _(3)};
int main() {
  for (auto i : states) cout << (sg(i) ? 'L' : 'V');
}
