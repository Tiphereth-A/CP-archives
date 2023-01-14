#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
template <uint32_t Ra = 129, uint32_t Rb = UINT32_MAX>
class HashStr2 {
  using self = HashStr2<Ra, Rb>;

protected:
  std::uniform_int_distribution<uint32_t> b_range;
  std::mt19937 e;
  const uint64_t mod1, mod2;
  uint32_t b;
  std::vector<std::pair<uint64_t, uint64_t>> p, hash;

public:
  explicit HashStr2(uint64_t mod1, uint64_t mod2, uint32_t base = 0)
    : b_range(Ra, Rb), e(), mod1(mod1), mod2(mod2) {
    reset_base(base);
  }
  self &reset_base(uint32_t base = 0) {
    if (!(b = base)) b = b_range(e);
    return *this;
  }
  self &reset(std::string_view str) {
    hash.resize(1, {0, 0});
    p.resize(1, {1, 1});
    for (auto &&ch : str) {
      hash.emplace_back((hash.back().first * b % mod1 + ch + 1) % mod1,
                        (hash.back().second * b % mod2 + ch + 1) % mod2);
      p.emplace_back(p.back().first * b % mod1, p.back().second * b % mod2);
    }
    return *this;
  }
  uint32_t get_base() const { return b; }
  std::pair<uint64_t, uint64_t> get(size_t pos, size_t len = SIZE_MAX) const {
    assert(pos < hash.size());
    auto &&end_ = hash[pos + std::min(len, hash.size() - 1 - pos)];
    return {
      (end_.first + mod1 - (int64_t)hash[pos].first * p[len].first % mod1) %
        mod1,
      (end_.second + mod2 - (int64_t)hash[pos].second * p[len].second % mod2) %
        mod2};
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  set<pair<u64, u64>> ss;
  HashStr2<> hashs(998244353, 1e9 + 7);
  for (int i = 0; i < t; ++i) {
    string str;
    cin >> str;
    hashs.reset(str);
    ss.insert(hashs.get(0));
  }
  cout << ss.size();
  return 0;
}
