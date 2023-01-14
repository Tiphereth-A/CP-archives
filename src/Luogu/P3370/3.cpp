#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
class HashStr2 {
protected:
  std::uniform_int_distribution<uint32_t> b_range;
  std::mt19937 e;
  const uint64_t mod1, mod2;
  uint32_t b;
  std::vector<std::pair<uint64_t, uint64_t>> p, hash;
  bool base_reseted_ = true;

public:
  explicit HashStr2(uint64_t mod1,
                    uint64_t mod2,
                    uint32_t base = 0,
                    uint32_t range_a = 129,
                    uint32_t range_b = UINT32_MAX)
    : b_range(range_a, range_b), e(), mod1(mod1), mod2(mod2) {
    reset_base(b = base);
  }
  HashStr2 &reset_base(uint32_t base = 0) {
    if (!(b = base)) b = b_range(e) % std::min(mod1, mod2);
    base_reseted_ = true;
    return *this;
  }
  HashStr2 &reset(std::string_view str) {
    hash.resize(1, {0, 0});
    for (auto &&ch : str)
      hash.emplace_back((hash.back().first * b % mod1 + ch + 1) % mod1,
                        (hash.back().second * b % mod2 + ch + 1) % mod2);
    if (base_reseted_) {
      p.resize(1, {1, 1});
      for (size_t i = 0; i < str.size(); ++i)
        p.emplace_back(p.back().first * b % mod1, p.back().second * b % mod2);
      base_reseted_ = false;
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
  HashStr2 hashs(998244353, 1e9 + 7);
  for (int i = 0; i < t; ++i) {
    string str;
    cin >> str;
    hashs.reset(str);
    ss.insert(hashs.get(0));
  }
  cout << ss.size();
  return 0;
}
