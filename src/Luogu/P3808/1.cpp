#include <bits/stdc++.h>
const int N = 1e6 + 5;
namespace AC_automaton {
template <typename _T,
          const char _str_begin,
          const char _str_end,
          const std::size_t _N,
          const bool _clear>
class _ACAM_Base {
protected:
  struct ACAM_t {
    std::size_t alpha[_str_end - _str_begin];
    std::size_t fail;
    bool end;
  };
  std::size_t cnt_nodes;
  bool builded;
  ACAM_t data[_N];
  _T e[_N];
  virtual void _insert_end(std::size_t p, std::size_t x) = 0;
  virtual void _query_mid(_T &res, std::size_t p) = 0;
  virtual void _query_end(_T &res) {}

public:
  _ACAM_Base() {
    cnt_nodes = builded = 0;
    if (_clear) memset(data, 0, sizeof(data));
  }
  virtual void clear() {
    cnt_nodes = builded = 0;
    memset(data, 0, sizeof(data));
  }
  void insert(const std::string &str, std::size_t x = 0) {
    std::size_t p = 0;
    for (std::size_t i = 0, c; i < str.size(); ++i) {
      if (!data[p].alpha[c = str[i] - _str_begin])
        data[p].alpha[c] = ++cnt_nodes;
      p = data[p].alpha[c];
    }
    data[p].end = true;
    _insert_end(p, x);
  }
  void build() {
    std::queue<std::size_t> q;
    for (std::size_t i : data[0].alpha)
      if (i) q.push(i);
    std::size_t p = 0;
    while (!q.empty()) {
      p = q.front();
      q.pop();
      for (std::size_t i = 0; i < _str_end - _str_begin; ++i) {
        if (data[p].alpha[i]) {
          data[data[p].alpha[i]].fail = data[data[p].fail].alpha[i];
          q.push(data[p].alpha[i]);
        } else data[p].alpha[i] = data[data[p].fail].alpha[i];
      }
    }
    builded = true;
  }
  _T query(const std::string &str) {
    if (!builded) build();
    std::size_t p = 0;
    _T res = 0;
    for (char c : str) _query_mid(res, p = data[p].alpha[c - _str_begin]);
    _query_end(res);
    return res;
  }
};
template <typename _T = std::ptrdiff_t,
          const char _str_begin = 'a',
          const char _str_end = 'z' + 1,
          const std::size_t _N = N,
          const bool _clear = false>
class ACAM: public _ACAM_Base<_T, _str_begin, _str_end, _N, _clear> {
protected:
  _T e[_N];
  void _insert_end(std::size_t p, std::size_t x) { ++e[p]; }
  void _query_mid(_T &res, std::size_t p) {
    for (std::size_t i = p; i && ~e[i]; i = this->data[i].fail) {
      res += e[i];
      e[i] = -1;
    }
  };
  void _query_end(_T &res) {};

public:
  ACAM() {
    if (_clear) memset(e, 0, sizeof(e));
  }
  void clear() {
    this->cnt_nodes = this->builded = 0;
    memset(this->data, 0, sizeof(this->data));
    memset(e, 0, sizeof(e));
  }
};
}  // namespace AC_automaton
using AC_automaton::ACAM;
ACAM<> acam;
int main() {
  int n;
  std::cin >> n;
  std::string str;
  while (n--) {
    std::cin >> str;
    acam.insert(str);
  }
  std::cin >> str;
  std::cout << acam.query(str);
  return 0;
}
