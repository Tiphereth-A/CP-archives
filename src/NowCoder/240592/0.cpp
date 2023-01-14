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
HashStr pre, suc;
vector<u64> calc(string_view s_) {
  string s;
  s.push_back('z' + 2);
  for (auto &&_ : s_) {
    s.push_back(_);
    s.push_back('z' + 2);
  }
  pre.reset(s);
  reverse(s.begin(), s.end());
  suc.reset(s);
  set<u64> v1;
  v1.insert(pre.get(0, 1));
  for (size_t l = 0, len_l, len_r, len_mid, len_ans; l < s.size(); ++l) {
    len_l = len_ans = 1;
    len_r = std::min(l + 1, s.size() - l);
    while (len_l <= len_r) {
      len_mid = (len_l + len_r) / 2;
      if (pre.get(l, len_mid) == suc.get(s.size() - l - 1, len_mid))
        len_l = (len_ans = len_mid) + 1;
      else len_r = len_mid - 1;
    }
    for (ptrdiff_t len_ = len_ans; len_ > 0; len_ -= 2) {
      auto &&__ = pre.get(l - len_ + 1, len_ * 2 - 1);
      if (v1.count(__)) break;
      v1.insert(__);
    }
  }
  vector<u64> vv;
  vv.reserve(v1.size());
  for (auto &&i : v1) vv.push_back(i);
  return vv;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  string s;
  cin >> t >> s;
  vector<u64> v1 = calc(s);
  for (--t; t; --t) {
    cin >> s;
    vector<u64> v2 = calc(s);
    v1.erase(
      set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v1.begin()),
      v1.end());
  }
  cout << v1.size() - 1;
  return 0;
}
