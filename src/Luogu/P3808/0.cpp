#include <bits/stdc++.h>
using namespace std;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e6 + OFFSET, M = 2e5 + OFFSET, K = 21;
template <typename _T = std::ptrdiff_t,
          const char _str_begin = 'a',
          const char _str_end = 'z' + 1,
          std::size_t _N = N,
          bool _clear = false>
class ACAM {
private:
  struct ACAM_t {
    std::size_t alpha[_str_end - _str_begin];
    std::size_t fail;
    bool end;
  };
  std::size_t cnt_nodes;
  bool builded;
  ACAM_t data[_N];
  _T e[_N];
  void _insert_end(std::size_t p, std::size_t x) { ++e[p]; }
  void _query_mid(_T &res, std::size_t p) {
    for (std::size_t i = p; i && ~e[i]; i = data[i].fail) {
      res += e[i];
      e[i] = -1;
    }
  };
  void _query_end(_T &res) {};

public:
  ACAM() {
    cnt_nodes = builded = 0;
    if (_clear) memset(data, 0, sizeof(data));
  }
  void clear() {
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
ACAM<> acam;
int e[N];
int main() {
  int n;
  cin >> n;
  string str;
  while (n--) {
    cin >> str;
    acam.insert(str);
  }
  cin >> str;
  cout << acam.query(str);
FINISHED:
  return 0;
}
