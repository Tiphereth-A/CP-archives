#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
class HashStr {
protected:
  static const uint64_t mod = (1ull << 61) - 1;
  static const uint64_t _2e30n1 = (1ul << 30) - 1, _2e31n1 = (1ul << 31) - 1;
  std::uniform_int_distribution<uint32_t> b_range;
  std::mt19937 e;
  uint32_t b;
  std::vector<uint64_t> p, hash;
  bool base_reseted_ = true;
  constexpr uint64_t mul_(uint64_t a, uint64_t b) const {
    uint64_t au = a >> 31, ad = a & _2e31n1;
    uint64_t bu = b >> 31, bd = b & _2e31n1;
    uint64_t _ = ad * bu + au * bd;
    return ((au * bu) << 1) + ad * bd + ((_ & _2e30n1) << 31) + (_ >> 30);
  }
  constexpr uint64_t mod_(uint64_t a) const {
    a = (a & mod) + (a >> 61);
    return a > mod ? a - mod : a;
  }

public:
  explicit HashStr(uint32_t base = 0,
                   uint32_t range_a = 129,
                   uint32_t range_b = UINT32_MAX)
    : b_range(129, range_b), e() {
    reset_base(b = base);
  }
  HashStr &reset_base(uint32_t base = 0) {
    if (!(b = base)) b = mod_(b_range(e));
    base_reseted_ = true;
    return *this;
  }
  HashStr &reset(std::string_view str) {
    hash.resize(1, 0);
    for (auto &&ch : str) hash.push_back(mod_(mul_(hash.back(), b) + ch + 1));
    if (base_reseted_) {
      p.resize(1, 1);
      for (size_t i = 0; i < str.size(); ++i)
        p.push_back(mod_(mul_(p.back(), b)));
      base_reseted_ = false;
    }
    return *this;
  }
  uint32_t get_base() const { return b; }
  uint64_t get(size_t pos, size_t len = SIZE_MAX) const {
    assert(pos < hash.size());
    auto &&end_ = hash[pos + std::min(len, hash.size() - 1 - pos)];
    return mod_(end_ + mod * 7 - mul_(hash[pos], p[len]));
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  set<u64> ss;
  HashStr hashs;
  for (int i = 0; i < t; ++i) {
    string str;
    cin >> str;
    hashs.reset(str);
    ss.insert(hashs.get(0));
  }
  cout << ss.size();
  return 0;
}
