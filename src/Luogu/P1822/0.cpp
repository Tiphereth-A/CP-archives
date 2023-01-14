#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
template <class Tp>
using vc = std::vector<Tp>;
namespace NdVector {
template <size_t N, class Tp>
struct ndvector: public std::vector<ndvector<N - 1, Tp>> {
  static_assert(N > 0, "N should be positive");
  using base_tp = ndvector<N - 1, Tp>;
  using base = std::vector<base_tp>;
  using self = ndvector<N, Tp>;
  template <class T, typename... Ts>
  ndvector(T &&n, Ts &&...args): base(n, base_tp(args...)) {}
  constexpr size_t dim() const { return N; }
  template <class T>
  void fill(T &&x) {
    for (auto &i : *this) i.fill(x);
  }
};
template <class Tp>
struct ndvector<1, Tp>: public std::vector<Tp> {
  using base = std::vector<Tp>;
  using self = ndvector<1, Tp>;
  template <class T>
  ndvector(T &&n): base(n) {}
  constexpr size_t dim() const { return 1; }
  template <class T>
  void fill(T &&x) {
    std::fill(this->begin(), this->end(), x);
  }
};
}  // namespace NdVector
struct CustomHash {
  static constexpr uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static constexpr size_t append(size_t x, size_t y) {
    return x ^ (y >> 1) ^ ((y & 1) << (sizeof(size_t) * 8 - 1));
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  template <class Tp, class Up>
  size_t operator()(std::pair<Tp, Up> const &p) const {
    return append((*this)(p.first), (*this)(p.second));
  }
  template <typename... Ts>
  size_t operator()(std::tuple<Ts...> const &tp) const {
    size_t ret = 0;
    std::apply(
      [&](Ts const &...targs) { ((ret = append(ret, (*this)(targs))), ...); },
      tp);
    return ret;
  }
  template <
    class Tp,
    std::enable_if_t<std::is_same<decltype(std::declval<Tp>().begin()),
                                  typename Tp::iterator>::value &&
                     std::is_same<decltype(std::declval<Tp>().end()),
                                  typename Tp::iterator>::value> * = nullptr>
  size_t operator()(Tp const &tp) const {
    size_t ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};
using u32 = uint32_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define rfor_(i, r, l, vars...)                                           \
  for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; \
       i >= i##end;                                                       \
       --i)
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define TPL_SIZE_(Tuple) std::tuple_size_v<std::remove_reference_t<Tuple>>
namespace tuple_detail_ {
template <std::size_t Begin, class Tuple, std::size_t... Is>
constexpr auto subtuple_impl_(Tuple &&t, std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is + Begin>(t)...);
}
template <class Tuple, class BinOp, std::size_t... Is>
constexpr auto
apply2_impl_(BinOp &&f, Tuple &&lhs, Tuple &&rhs, std::index_sequence<Is...>) {
  return std::make_tuple(
    std::forward<BinOp>(f)(std::get<Is>(lhs), std::get<Is>(rhs))...);
}
}  // namespace tuple_detail_
template <std::size_t Begin, std::size_t Len, class Tuple>
constexpr auto subtuple(Tuple &&t) {
  static_assert(Begin <= TPL_SIZE_(Tuple) && Len <= TPL_SIZE_(Tuple) &&
                  Begin + Len <= TPL_SIZE_(Tuple),
                "Out of range");
  return tuple_detail_::subtuple_impl_<Begin>(t,
                                              std::make_index_sequence<Len>());
}
template <std::size_t Pos, class Tp, class Tuple>
constexpr auto tuple_push(Tp &&v, Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        std::make_tuple(v),
                        subtuple<Pos, TPL_SIZE_(Tuple) - Pos>(t));
}
template <class Tp, class Tuple>
constexpr auto tuple_push_front(Tp &&v, Tuple &&t) {
  return tuple_push<0>(v, t);
}
template <class Tp, class Tuple>
constexpr auto tuple_push_back(Tp &&v, Tuple &&t) {
  return tuple_push<TPL_SIZE_(Tuple)>(v, t);
}
template <std::size_t Pos, class Tuple>
constexpr auto tuple_pop(Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        subtuple<Pos + 1, TPL_SIZE_(Tuple) - Pos - 1>(t));
}
template <class Tuple>
constexpr auto tuple_pop_front(Tuple &&t) {
  return tuple_pop<0>(t);
}
template <class Tuple>
constexpr auto tuple_pop_back(Tuple &&t) {
  return tuple_pop<TPL_SIZE_(Tuple) - 1>(t);
}
template <class Tuple, class BinOp>
constexpr auto apply2(BinOp &&f, Tuple &&lhs, Tuple &&rhs) {
  return tuple_detail_::apply2_impl_(
    f, lhs, rhs, std::make_index_sequence<TPL_SIZE_(Tuple)>());
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return std::pair<Tp, Up>{lhs.first op rhs.first,                          \
                             lhs.second op rhs.second};                       \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op(std::tuple<Ts...> const &lhs,                    \
                             std::tuple<Ts...> const &rhs) {                  \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs,                       \
                                const std::tuple<Ts...> &rhs) {               \
    return lhs = lhs op rhs;                                                  \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
#undef TPL_SIZE_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &p) {
  std::apply(
    [&](Ts const &...targs) {
      std::size_t n{0};
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <
  class Ch,
  class Tr,
  class Ct,
  std::enable_if_t<std::is_same<decltype(std::declval<Ct>().begin()),
                                typename Ct::iterator>::value &&
                   std::is_same<decltype(std::declval<Ct>().end()),
                                typename Ct::iterator>::value> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
using namespace std;
const int B = 1e6;
const int table[1001] = {
  0,      2045,   3089,   3839,   4196,   4512,   4828,   5186,   5935,
  6979,   8453,   9319,   10363,  10666,  10886,  11040,  11155,  11239,
  11364,  11710,  12637,  13015,  13573,  14323,  14544,  14748,  14902,
  15020,  15154,  15300,  15682,  15792,  16062,  16365,  16722,  16898,
  17102,  17270,  17398,  17487,  17562,  17647,  17773,  18071,  18292,
  18608,  18784,  19004,  19172,  19260,  19329,  19398,  19486,  19654,
  19874,  20050,  20366,  20587,  20885,  21011,  21096,  21171,  21260,
  21388,  21556,  21760,  21936,  22293,  22596,  22866,  22977,  23359,
  23504,  23638,  23756,  23910,  24114,  24336,  25085,  25643,  26021,
  26948,  27295,  27419,  27503,  27618,  27772,  27992,  28295,  29339,
  30205,  32227,  32981,  33205,  33276,  33362,  33477,  33645,  33943,
  34501,  35975,  36601,  37159,  37277,  37358,  37409,  37442,  37461,
  37491,  37807,  39268,  40134,  41178,  41481,  41701,  41855,  41970,
  42054,  42179,  42525,  43452,  43562,  44120,  44214,  44435,  44531,
  44608,  44656,  44688,  44714,  44774,  44848,  45118,  45234,  45300,
  45395,  45599,  45717,  45800,  45855,  45884,  45934,  46060,  46178,
  46255,  46305,  46381,  46494,  46662,  46719,  46762,  46806,  46894,
  47002,  47081,  47121,  47162,  47206,  47297,  47395,  47480,  47521,
  47610,  47679,  47760,  47794,  47817,  47847,  47868,  47948,  48015,
  48151,  48296,  48370,  48434,  48485,  48506,  48528,  48552,  48587,
  48640,  49129,  49476,  49551,  49612,  49663,  49687,  49700,  49728,
  49900,  49979,  51122,  51876,  51923,  51968,  52019,  52055,  52070,
  52090,  52319,  53243,  53483,  53723,  54021,  54139,  54208,  54259,
  54287,  54330,  54393,  54978,  55844,  56172,  56475,  56588,  56665,
  56716,  56751,  56776,  56838,  57213,  57591,  58149,  58899,  59120,
  59324,  59478,  59596,  59730,  59876,  60258,  60325,  60519,  60822,
  60906,  61082,  61178,  61259,  61308,  61340,  61365,  61412,  61510,
  61808,  61934,  62003,  62098,  62318,  62426,  62478,  62516,  62559,
  62616,  62784,  62897,  62973,  63023,  63100,  63218,  63344,  63394,
  63442,  63511,  63639,  63757,  63817,  63857,  63891,  63920,  64016,
  64090,  64246,  64343,  64477,  64553,  64630,  64664,  64691,  64714,
  64740,  64795,  64957,  65150,  65274,  65328,  65397,  65448,  65471,
  65494,  65529,  65566,  65877,  66192,  66416,  66451,  66509,  66560,
  66582,  66610,  66682,  66959,  66984,  67062,  67180,  67348,  67413,
  67471,  67506,  67533,  67547,  67561,  67943,  68035,  68151,  68371,
  68472,  68541,  68594,  68627,  68666,  68698,  68808,  69366,  69460,
  69681,  69777,  69854,  69902,  69934,  69960,  70020,  70130,  70400,
  70703,  71060,  71236,  71440,  71608,  71736,  71825,  71900,  71934,
  72017,  72135,  72356,  72420,  72596,  72709,  72818,  72860,  72887,
  72925,  72977,  73085,  73305,  73400,  73469,  73595,  73893,  73991,
  74038,  74073,  74127,  74196,  74364,  74460,  74536,  74595,  74660,
  74854,  74964,  75015,  75081,  75155,  75273,  75374,  75434,  75478,
  75508,  75555,  75693,  75725,  75785,  75860,  75944,  76009,  76086,
  76138,  76159,  76184,  76217,  76241,  76282,  76329,  76400,  76452,
  76521,  76577,  76611,  76646,  76662,  76685,  76732,  76823,  76941,
  77056,  77108,  77153,  77188,  77204,  77219,  77389,  77453,  77518,
  77631,  77785,  77850,  77911,  77943,  77975,  77995,  78373,  78613,
  78692,  78818,  79022,  79123,  79187,  79233,  79260,  79314,  79381,
  79575,  79878,  79962,  80138,  80234,  80315,  80364,  80396,  80421,
  80506,  80632,  80930,  81151,  81467,  81643,  81863,  82031,  82119,
  82188,  82215,  82257,  82366,  82479,  82655,  82719,  82940,  83058,
  83141,  83175,  83204,  83259,  83342,  83460,  83664,  83759,  83825,
  83941,  84211,  84285,  84326,  84375,  84453,  84529,  84683,  84779,
  84856,  84889,  84967,  85077,  85100,  85146,  85195,  85249,  85364,
  85465,  85544,  85573,  85596,  85648,  85663,  85685,  85738,  85773,
  85859,  85924,  86005,  86057,  86083,  86095,  86107,  86133,  86185,
  86266,  86331,  86417,  86452,  86505,  86527,  86542,  86594,  86617,
  86646,  86725,  86826,  86941,  86995,  87044,  87090,  87113,  87223,
  87301,  87334,  87411,  87507,  87661,  87737,  87815,  87864,  87905,
  87979,  88249,  88365,  88431,  88526,  88730,  88848,  88931,  88986,
  89015,  89049,  89132,  89250,  89471,  89535,  89711,  89824,  89933,
  89975,  90002,  90071,  90159,  90327,  90547,  90723,  91039,  91260,
  91558,  91684,  91769,  91794,  91826,  91875,  91956,  92052,  92228,
  92312,  92615,  92809,  92876,  92930,  92957,  93003,  93067,  93168,
  93372,  93498,  93577,  93817,  94195,  94215,  94247,  94279,  94340,
  94405,  94559,  94672,  94737,  94801,  94971,  94986,  95002,  95037,
  95082,  95134,  95249,  95367,  95458,  95505,  95528,  95544,  95579,
  95613,  95669,  95738,  95790,  95861,  95908,  95949,  95973,  96006,
  96031,  96052,  96104,  96181,  96246,  96330,  96405,  96465,  96497,
  96635,  96682,  96712,  96756,  96816,  96917,  97035,  97109,  97175,
  97226,  97336,  97530,  97595,  97654,  97730,  97826,  97994,  98063,
  98117,  98152,  98199,  98297,  98595,  98721,  98790,  98885,  99105,
  99213,  99265,  99303,  99330,  99372,  99481,  99594,  99770,  99834,
  100055, 100173, 100256, 100290, 100365, 100454, 100582, 100750, 100954,
  101130, 101487, 101790, 102060, 102170, 102230, 102256, 102288, 102336,
  102413, 102509, 102730, 102824, 103382, 103492, 103524, 103563, 103596,
  103649, 103718, 103819, 104039, 104155, 104247, 104629, 104643, 104657,
  104684, 104719, 104777, 104842, 105010, 105128, 105206, 105232, 105508,
  105580, 105608, 105630, 105681, 105739, 105775, 105999, 106314, 106624,
  106661, 106696, 106719, 106742, 106793, 106862, 106916, 107041, 107234,
  107395, 107450, 107476, 107499, 107526, 107560, 107637, 107713, 107847,
  107945, 108100, 108174, 108270, 108299, 108333, 108373, 108433, 108551,
  108679, 108748, 108796, 108846, 108972, 109090, 109167, 109217, 109293,
  109406, 109574, 109631, 109674, 109712, 109764, 109872, 110092, 110187,
  110256, 110382, 110680, 110778, 110825, 110850, 110882, 110931, 111012,
  111108, 111284, 111368, 111671, 111865, 111933, 112315, 112460, 112594,
  112712, 112866, 113070, 113292, 114041, 114599, 114978, 115352, 115414,
  115439, 115474, 115525, 115602, 115715, 116019, 116346, 117213, 117797,
  117860, 117903, 117931, 117982, 118051, 118169, 118467, 118708, 118947,
  119871, 120100, 120120, 120135, 120171, 120222, 120267, 120314, 121068,
  122211, 122290, 122462, 122490, 122503, 122527, 122578, 122639, 122715,
  123061, 123550, 123603, 123638, 123662, 123684, 123705, 123756, 123820,
  123894, 124039, 124175, 124242, 124322, 124343, 124373, 124396, 124430,
  124511, 124580, 124669, 124710, 124795, 124893, 124984, 125028, 125069,
  125109, 125188, 125296, 125384, 125428, 125471, 125528, 125696, 125809,
  125885, 125935, 126012, 126130, 126256, 126306, 126335, 126390, 126473,
  126591, 126795, 126890, 126956, 127072, 127342, 127416, 127476, 127502,
  127534, 127582, 127659, 127755, 127976, 128070, 128628, 128738, 129665,
  130012, 130136, 130220, 130335, 130489, 130709, 131012, 132056, 132922,
  134383, 134699, 134729, 134748, 134781, 134832, 134913, 135031, 135589,
  136215, 139782, 142039, 142127, 142133, 142153, 142186, 142221, 142275,
  142589, 144611, 144982, 145988, 146122, 146131, 146140, 146176, 146229,
  146279, 146471, 147398, 147455, 147527, 147611, 147625, 147636, 147660,
  147708, 147786, 147884, 148266, 148312, 148353, 148376, 148394, 148403,
  148424, 148480, 148563, 148632, 148707, 148757, 148840, 148892, 148919,
  148940, 148963, 149015, 149124, 149181, 149250, 149294, 149382, 149490,
  149569, 149609, 149650, 149694, 149785, 149883, 149968, 150003, 150057,
  150126, 150294, 150390, 150466, 150525, 150590, 150784, 150894, 150948,
  150975, 151021, 151085, 151186, 151390, 151516, 151595, 151835, 152214,
  152588, 152650, 152675, 152710, 152761, 152838, 152951, 153255, 153582,
  154448, 156470, 157224, 157448, 157519, 157605, 157720, 157888, 158186,
  158744, 160218};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  auto magic = [](int n) -> int {
    int x = 0;
    vc<int> a;
    while (n > 0) {
      a.push_back(n % 10);
      n /= 10;
    }
    rfor_(j, a.size() - 1, 1) (x *= 10) += abs(a[j] - a[j - 1]);
    return x;
  };
  auto chk = [&](int n) -> bool {
    while (n > 9) n = magic(n);
    return n == 7;
  };
  auto f = [&](int n) -> int {
    int m = n % B;
    int ans = table[n /= B];
    m += (n *= B);
    for_(i, n + 1, m) ans += chk(i);
    return ans;
  };
  int a, b;
  cin >> a >> b;
  cout << f(b) - f(a - 1) << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
