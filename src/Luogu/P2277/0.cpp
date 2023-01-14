#include <bits/stdc++.h>
using namespace std;
#define _SEL3(_1, _2, _3, ...) _1, _2, _3
#define SEL3(...) _SEL3(__VA_ARGS__)
#define _CPROD1_4_HELPER(a, b, c, d, ...) \
  a, __VA_ARGS__, b, __VA_ARGS__, c, __VA_ARGS__, d, __VA_ARGS__
#define _CPROD2_4_HELPER(a, b, c, d, ...)         \
  _CPROD1_4_HELPER(a, b, c, d, a, __VA_ARGS__),   \
    _CPROD1_4_HELPER(a, b, c, d, b, __VA_ARGS__), \
    _CPROD1_4_HELPER(a, b, c, d, c, __VA_ARGS__), \
    _CPROD1_4_HELPER(a, b, c, d, d, __VA_ARGS__)
#define CPROD3_4(a, b, c, d)                                        \
  _CPROD2_4_HELPER(a, b, c, d, a), _CPROD2_4_HELPER(a, b, c, d, b), \
    _CPROD2_4_HELPER(a, b, c, d, c), _CPROD2_4_HELPER(a, b, c, d, d)
#define RMAB(a, b, ...) _RM_##b(RM##a, __VA_ARGS__)
#define OPANDS CPROD3_4(+, -, *, /)
#define OPS0 SEL3(OPANDS)
#define OPS1 SEL3(RMAB(3, 1, OPANDS))
#define OPS2 SEL3(RMAB(3, 2, OPANDS))
#define OPS3 SEL3(RMAB(3, 3, OPANDS))
#define OPS4 SEL3(RMAB(3, 4, OPANDS))
#define OPS5 SEL3(RMAB(3, 5, OPANDS))
#define OPS6 SEL3(RMAB(3, 6, OPANDS))
#define OPS7 SEL3(RMAB(3, 7, OPANDS))
#define OPS8 SEL3(RMAB(3, 8, OPANDS))
#define OPS9 SEL3(RMAB(3, 9, OPANDS))
#define OPS10 SEL3(RMAB(3, 10, OPANDS))
#define OPS11 SEL3(RMAB(3, 11, OPANDS))
#define OPS12 SEL3(RMAB(3, 12, OPANDS))
#define OPS13 SEL3(RMAB(3, 13, OPANDS))
#define OPS14 SEL3(RMAB(3, 14, OPANDS))
#define OPS15 SEL3(RMAB(3, 15, OPANDS))
#define OPS16 SEL3(RMAB(3, 16, OPANDS))
#define OPS17 SEL3(RMAB(3, 17, OPANDS))
#define OPS18 SEL3(RMAB(3, 18, OPANDS))
#define OPS19 SEL3(RMAB(3, 19, OPANDS))
#define OPS20 SEL3(RMAB(3, 20, OPANDS))
#define OPS21 SEL3(RMAB(3, 21, OPANDS))
#define OPS22 SEL3(RMAB(3, 22, OPANDS))
#define OPS23 SEL3(RMAB(3, 23, OPANDS))
#define OPS24 SEL3(RMAB(3, 24, OPANDS))
#define OPS25 SEL3(RMAB(3, 25, OPANDS))
#define OPS26 SEL3(RMAB(3, 26, OPANDS))
#define OPS27 SEL3(RMAB(3, 27, OPANDS))
#define OPS28 SEL3(RMAB(3, 28, OPANDS))
#define OPS29 SEL3(RMAB(3, 29, OPANDS))
#define OPS30 SEL3(RMAB(3, 30, OPANDS))
#define OPS31 SEL3(RMAB(3, 31, OPANDS))
#define OPS32 SEL3(RMAB(3, 32, OPANDS))
#define OPS33 SEL3(RMAB(3, 33, OPANDS))
#define OPS34 SEL3(RMAB(3, 34, OPANDS))
#define OPS35 SEL3(RMAB(3, 35, OPANDS))
#define OPS36 SEL3(RMAB(3, 36, OPANDS))
#define OPS37 SEL3(RMAB(3, 37, OPANDS))
#define OPS38 SEL3(RMAB(3, 38, OPANDS))
#define OPS39 SEL3(RMAB(3, 39, OPANDS))
#define OPS40 SEL3(RMAB(3, 40, OPANDS))
#define OPS41 SEL3(RMAB(3, 41, OPANDS))
#define OPS42 SEL3(RMAB(3, 42, OPANDS))
#define OPS43 SEL3(RMAB(3, 43, OPANDS))
#define OPS44 SEL3(RMAB(3, 44, OPANDS))
#define OPS45 SEL3(RMAB(3, 45, OPANDS))
#define OPS46 SEL3(RMAB(3, 46, OPANDS))
#define OPS47 SEL3(RMAB(3, 47, OPANDS))
#define OPS48 SEL3(RMAB(3, 48, OPANDS))
#define OPS49 SEL3(RMAB(3, 49, OPANDS))
#define OPS50 SEL3(RMAB(3, 50, OPANDS))
#define OPS51 SEL3(RMAB(3, 51, OPANDS))
#define OPS52 SEL3(RMAB(3, 52, OPANDS))
#define OPS53 SEL3(RMAB(3, 53, OPANDS))
#define OPS54 SEL3(RMAB(3, 54, OPANDS))
#define OPS55 SEL3(RMAB(3, 55, OPANDS))
#define OPS56 SEL3(RMAB(3, 56, OPANDS))
#define OPS57 SEL3(RMAB(3, 57, OPANDS))
#define OPS58 SEL3(RMAB(3, 58, OPANDS))
#define OPS59 SEL3(RMAB(3, 59, OPANDS))
#define OPS60 SEL3(RMAB(3, 60, OPANDS))
#define OPS61 SEL3(RMAB(3, 61, OPANDS))
#define OPS62 SEL3(RMAB(3, 62, OPANDS))
#define OPS63 RMAB(3, 63, OPANDS)
#define ___CALC0(a, b, c, d, opab, opbc, opcd) \
  Node(0,                                      \
       a,                                      \
       b,                                      \
       c,                                      \
       d,                                      \
       #opab,                                  \
       #opbc,                                  \
       #opcd,                                  \
       ((double(a) opab double(b))opbc double(c))opcd double(d))
#define ___CALC1(a, b, c, d, opab, opbc, opcd) \
  Node(1,                                      \
       a,                                      \
       b,                                      \
       c,                                      \
       d,                                      \
       #opab,                                  \
       #opbc,                                  \
       #opcd,                                  \
       (double(a) opab(double(b) opbc double(c)))opcd double(d))
#define ___CALC2(a, b, c, d, opab, opbc, opcd) \
  Node(2,                                      \
       a,                                      \
       b,                                      \
       c,                                      \
       d,                                      \
       #opab,                                  \
       #opbc,                                  \
       #opcd,                                  \
       double(a) opab((double(b) opbc double(c))opcd double(d)))
#define ___CALC3(a, b, c, d, opab, opbc, opcd) \
  Node(3,                                      \
       a,                                      \
       b,                                      \
       c,                                      \
       d,                                      \
       #opab,                                  \
       #opbc,                                  \
       #opcd,                                  \
       double(a) opab(double(b) opbc(double(c) opcd double(d))))
#define ___CALC4(a, b, c, d, opab, opbc, opcd) \
  Node(4,                                      \
       a,                                      \
       b,                                      \
       c,                                      \
       d,                                      \
       #opab,                                  \
       #opbc,                                  \
       #opcd,                                  \
       ((double(a) opab double(b))opbc(double(c) opcd double(d))))
#define ___CALC(a, b, c, d, opab, opbc, opcd) \
  ___CALC0(a, b, c, d, opab, opbc, opcd),     \
    ___CALC1(a, b, c, d, opab, opbc, opcd),   \
    ___CALC2(a, b, c, d, opab, opbc, opcd),   \
    ___CALC3(a, b, c, d, opab, opbc, opcd),   \
    ___CALC4(a, b, c, d, opab, opbc, opcd)
#define __CALC(...) ___CALC(__VA_ARGS__)
#define _CALC(a, b, c, d)                                 \
  __CALC(a, b, c, d, OPS0), __CALC(a, b, c, d, OPS1),     \
    __CALC(a, b, c, d, OPS2), __CALC(a, b, c, d, OPS3),   \
    __CALC(a, b, c, d, OPS4), __CALC(a, b, c, d, OPS5),   \
    __CALC(a, b, c, d, OPS6), __CALC(a, b, c, d, OPS7),   \
    __CALC(a, b, c, d, OPS8), __CALC(a, b, c, d, OPS9),   \
    __CALC(a, b, c, d, OPS10), __CALC(a, b, c, d, OPS11), \
    __CALC(a, b, c, d, OPS12), __CALC(a, b, c, d, OPS13), \
    __CALC(a, b, c, d, OPS14), __CALC(a, b, c, d, OPS15), \
    __CALC(a, b, c, d, OPS16), __CALC(a, b, c, d, OPS17), \
    __CALC(a, b, c, d, OPS18), __CALC(a, b, c, d, OPS19), \
    __CALC(a, b, c, d, OPS20), __CALC(a, b, c, d, OPS21), \
    __CALC(a, b, c, d, OPS22), __CALC(a, b, c, d, OPS23), \
    __CALC(a, b, c, d, OPS24), __CALC(a, b, c, d, OPS25), \
    __CALC(a, b, c, d, OPS26), __CALC(a, b, c, d, OPS27), \
    __CALC(a, b, c, d, OPS28), __CALC(a, b, c, d, OPS29), \
    __CALC(a, b, c, d, OPS30), __CALC(a, b, c, d, OPS31), \
    __CALC(a, b, c, d, OPS32), __CALC(a, b, c, d, OPS33), \
    __CALC(a, b, c, d, OPS34), __CALC(a, b, c, d, OPS35), \
    __CALC(a, b, c, d, OPS36), __CALC(a, b, c, d, OPS37), \
    __CALC(a, b, c, d, OPS38), __CALC(a, b, c, d, OPS39), \
    __CALC(a, b, c, d, OPS40), __CALC(a, b, c, d, OPS41), \
    __CALC(a, b, c, d, OPS42), __CALC(a, b, c, d, OPS43), \
    __CALC(a, b, c, d, OPS44), __CALC(a, b, c, d, OPS45), \
    __CALC(a, b, c, d, OPS46), __CALC(a, b, c, d, OPS47), \
    __CALC(a, b, c, d, OPS48), __CALC(a, b, c, d, OPS49), \
    __CALC(a, b, c, d, OPS50), __CALC(a, b, c, d, OPS51), \
    __CALC(a, b, c, d, OPS52), __CALC(a, b, c, d, OPS53), \
    __CALC(a, b, c, d, OPS54), __CALC(a, b, c, d, OPS55), \
    __CALC(a, b, c, d, OPS56), __CALC(a, b, c, d, OPS57), \
    __CALC(a, b, c, d, OPS58), __CALC(a, b, c, d, OPS59), \
    __CALC(a, b, c, d, OPS60), __CALC(a, b, c, d, OPS61), \
    __CALC(a, b, c, d, OPS62), __CALC(a, b, c, d, OPS63),
#define CALC(...) _CALC(__VA_ARGS__)
int dict[256];
dict['+'] = 0;
dict['-'] = 1;
dict['*'] = 2;
dict['/'] = 3;
return 0;
}
();
struct Node {
  u64 hash;
  double data;
  Node(const int &type,
       i64 a,
       i64 b,
       i64 c,
       i64 d,
       const char *opab,
       const char *opbc,
       const char *opcd,
       const double &_data)
    : data(_data) {
    switch (type) {
      case 0: break;
      case 1:
        if (!valid(dict[*opab], dict[*opbc])) {
          data = 0;
          break;
        }
        break;
      case 2:
        if (!valid(dict[*opab], dict[*opcd])) {
          data = 0;
          break;
        }
        break;
      case 3:
        if (!valid(dict[*opab], dict[*opbc]) ||
            !valid(dict[*opbc], dict[*opcd])) {
          data = 0;
          break;
        }
        break;
      case 4:
        if (!valid(dict[*opbc], dict[*opcd])) {
          data = 0;
          break;
        }
        if (!(dict[*opbc] & 1)) {
        } else {
        }
        break;
    }
    hash = 0;
    (hash += a) <<= 7;
    (hash += b) <<= 7;
    (hash += c) <<= 7;
    (hash += d) <<= 2;
    (hash += dict[*opab]) <<= 2;
    (hash += dict[*opbc]) <<= 2;
    (hash += dict[*opcd]) <<= 3;
    hash += type;
#undef minmax
  }
  constexpr bool valid(const int &a, const int &b) const {
    if (a == 0) return b > 1;
    if (a == 2) return b < 2;
    return true;
  }
  bool operator<(const Node &rhs) const { return hash < rhs.hash; }
};
void decode(u64 hash) {
#define _decode(val, n)        \
  val = hash & ((1 << n) - 1); \
  hash >>= n
  static const char _[] = "+-*/";
  int type, a, b, c, d, opab, opbc, opcd;
  _decode(type, 3);
  _decode(opcd, 2);
  _decode(opbc, 2);
  _decode(opab, 2);
  _decode(d, 7);
  _decode(c, 7);
  _decode(b, 7);
  _decode(a, 7);
  switch (type) {
    case 0:
      cerr << "(((" << a << " " << _[opab] << " " << b << ") " << _[opbc] << " "
           << c << ") " << _[opcd] << " " << d << ")" << endl;
      break;
    case 1:
      cerr << "((" << a << " " << _[opab] << " (" << b << " " << _[opbc] << " "
           << c << ")) " << _[opcd] << " " << d << ")" << endl;
      break;
    case 2:
      cerr << "(" << a << " " << _[opab] << " ((" << b << " " << _[opbc] << " "
           << c << ") " << _[opcd] << " " << d << "))" << endl;
      break;
    case 3:
      cerr << "(" << a << " " << _[opab] << " (" << b << " " << _[opbc] << " ("
           << c << " " << _[opcd] << " " << d << ")))" << endl;
      break;
    case 4:
      cerr << "((" << a << " " << _[opab] << " " << b << ") " << _[opbc] << " ("
           << c << " " << _[opcd] << " " << d << "))" << endl;
      break;
  }
#undef _decode
}
int main() {
  i64 a, b, c, d;
  cin >> a >> b >> c >> d;
  set<Node> s;
  vector<double> v{a, b, c, d};
  sort(v.begin(), v.end());
  do {
    s.merge(decltype(s){CALC(v[0], v[1], v[2], v[3])});
  } while (next_permutation(v.begin(), v.end()));
  int cnt = 0;
  for (const auto &[hash, data] : s)
    if (abs(data - 24) <= 1e-7) { ++cnt; }
  cout << cnt;
  return 0;
}
