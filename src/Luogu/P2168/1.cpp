#include <bits/stdc++.h>
using namespace std;
#define OPERATOR_OVERRIED_PAIR_(oper)                                         \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator oper##=(                              \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                   \
    lhs.first oper## = rhs.first;                                             \
    lhs.second oper## = rhs.second;                                           \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,            \
                                            const std::pair<Tp, Up> &rhs) {   \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> &operator oper##=(                         \
    std::tuple<Tp, Up, Vp> &lhs, const std::tuple<Tp, Up, Vp> &rhs) {         \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> operator oper(                             \
    std::tuple<Tp, Up, Vp> lhs, const std::tuple<Tp, Up, Vp> &rhs) {          \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> &operator oper##=(                     \
    std::tuple<Tp, Up, Vp, Wp> &lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) { \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    std::get<3>(lhs) oper## = std::get<3>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> operator oper(                         \
    std::tuple<Tp, Up, Vp, Wp> lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) {  \
    return lhs oper## = rhs;                                                  \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <class Ch, class Tr, class Tp, class Up>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Ch, class Tr, class Tp, class Up>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp, Wp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p) >>
         std::get<3>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp, Wp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p)
            << ' ' << std::get<3>(p);
}
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <class Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
template <typename Wp = size_t>
class Huffman_tree {
  using self = Huffman_tree<Wp>;

protected:
  struct Node {
    Wp weight;
    std::vector<size_t> children;
    Node(const Wp &weight = Wp{}, size_t child_cnt = 0)
      : weight(weight), children(child_cnt) {}
  };
  size_t cnt_w, cnt_l, ch_sz;
  std::vector<Node> data;

private:
  template <class Result,
            class Op = std::function<Result(const Result &, size_t)>>
  std::vector<Result> _operate(Op operate) const {
    std::vector<Result> ret(cnt_w);
    std::queue<std::pair<size_t, Result>> q;
    q.emplace(data.size() - 1, Result{});
    while (!q.empty()) {
      auto &&[now_idx, now_code] = q.front();
      auto &&children = data[now_idx].children;
      q.pop();
      for (size_t i = 0; i < ch_sz; ++i) {
        auto &&next_child = children[i];
        if (next_child < cnt_l) {
          if (next_child < cnt_w) ret[next_child] = operate(now_code, i);
          continue;
        } else q.emplace(next_child, operate(now_code, i));
      }
    }
    return ret;
  }

public:
  Huffman_tree() = delete;
  Huffman_tree(size_t child_size, const std::vector<Wp> &weights) {
    rebuild(child_size, weights);
  };
  self &rebuild(size_t child_size, const std::vector<Wp> &weights) {
    ch_sz = child_size;
    cnt_w = weights.size();
    data.clear();
    for (auto &&now : weights) data.emplace_back(now);
    for (size_t
           i = 0,
           iend = ((ch_sz - 1) - ((cnt_w - 1) % (ch_sz - 1))) % (ch_sz - 1);
         i < iend;
         ++i)
      data.emplace_back();
    cnt_l = data.size();
    std::priority_queue<std::pair<Wp, size_t>,
                        std::vector<std::pair<Wp, size_t>>,
                        std::greater<std::pair<Wp, size_t>>>
      q;
    for (size_t i = 0; i < data.size(); ++i) q.emplace(data[i].weight, i);
    while (q.size() > 1) {
      data.emplace_back(Wp{}, ch_sz);
      for (size_t i = 0; i < ch_sz; ++i) {
        auto &&[now_weight, now_idx] = q.top();
        data.back().weight += now_weight;
        data.back().children[i] = now_idx;
        q.pop();
      }
      q.emplace(data.back().weight, data.size() - 1);
    }
    return *this;
  }
  std::vector<std::string> encode(std::string_view char_set = "01") const {
    assert(char_set.size() == ch_sz);
    return _operate<std::string>([&](const std::string &pre_code, size_t idx) {
      return pre_code + char_set[idx];
    });
  }
  std::vector<size_t> depths() const {
    return _operate<size_t>(
      [](const size_t &pre_depth, size_t idx) { return pre_depth + 1; });
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  size_t n, k;
  cin >> n >> k;
  read_container_(vc<size_t>, w, n);
  Huffman_tree<> tr(k, w);
  size_t tot = 0, maxd = 0;
  auto &&dep = tr.depths();
  for_(i, 0, n - 1) {
    tot += dep[i] * w[i];
    chkmax(maxd, dep[i]);
  }
  cout << tot << '\n' << maxd << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
