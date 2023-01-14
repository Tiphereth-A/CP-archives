#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
namespace AC_automaton {
template <typename _T,
          const char _str_begin,
          const char _str_end,
          const size_t _N,
          const bool _clear>
class _ACAM_Base {
protected:
  struct ACAM_t {
    size_t alpha[_str_end - _str_begin];
    size_t fail;
    bool end;
  };
  size_t cnt_nodes;
  bool builded;
  ACAM_t data[_N];
  virtual void _insert_end(size_t p, size_t x) = 0;
  virtual void _query_mid(_T &res, size_t p) = 0;
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
  void insert(const string &str, size_t x = 0) {
    size_t p = 0;
    for (size_t i = 0, c; i < str.size(); ++i) {
      if (!data[p].alpha[c = str[i] - _str_begin])
        data[p].alpha[c] = ++cnt_nodes;
      p = data[p].alpha[c];
    }
    data[p].end = true;
    _insert_end(p, x);
  }
  void build() {
    queue<size_t> q;
    for (size_t i : data[0].alpha)
      if (i) q.push(i);
    size_t p = 0;
    while (!q.empty()) {
      p = q.front();
      q.pop();
      for (size_t i = 0; i < _str_end - _str_begin; ++i) {
        if (data[p].alpha[i]) {
          data[data[p].alpha[i]].fail = data[data[p].fail].alpha[i];
          q.push(data[p].alpha[i]);
        } else data[p].alpha[i] = data[data[p].fail].alpha[i];
      }
    }
    builded = true;
  }
  _T query(const string &str) {
    if (!builded) build();
    size_t p = 0;
    _T res = 0;
    for (char c : str) _query_mid(res, p = data[p].alpha[c - _str_begin]);
    _query_end(res);
    return res;
  }
};
template <typename _T = ptrdiff_t,
          const char _str_begin = 'a',
          const char _str_end = 'z' + 1,
          const size_t _N = N,
          const bool _clear = false>
class ACAM: public _ACAM_Base<_T, _str_begin, _str_end, _N, _clear> {
protected:
  _T idx[_N], val[_N];
  void _insert_end(size_t p, size_t x) { idx[p] = x; }
  void _query_mid(_T &res, size_t p) {
    for (size_t i = p; i; i = this->data[i].fail) ++val[i];
  };
  void _query_end(_T &res) {
    for (size_t i = 0; i <= this->cnt_nodes; ++i)
      if (idx[i]) res = max(res, cnt[idx[i]] = val[i]);
  };

public:
  _T cnt[_N];
  ACAM() {
    if (_clear) {
      memset(idx, 0, sizeof(idx));
      memset(val, 0, sizeof(val));
      memset(cnt, 0, sizeof(cnt));
    }
  }
  void clear() {
    this->cnt_nodes = this->builded = 0;
    memset(this->data, 0, sizeof(this->data));
    memset(idx, 0, sizeof(idx));
    memset(val, 0, sizeof(val));
    memset(cnt, 0, sizeof(cnt));
  }
};
}  // namespace AC_automaton
using AC_automaton::ACAM;
ACAM<> acam;
int main() {
  int n;
  while (cin >> n, n) {
    string str;
    vector<string> strs;
    for (int i = 1; i <= n; ++i) {
      cin >> str;
      strs.push_back(str);
      acam.insert(str, i);
    }
    cin >> str;
    auto res = acam.query(str);
    cout << res << endl;
    for (int i = 1; i <= n; ++i)
      if (acam.cnt[i] == res) cout << strs[i - 1] << endl;
    acam.clear();
  }
  return 0;
}
