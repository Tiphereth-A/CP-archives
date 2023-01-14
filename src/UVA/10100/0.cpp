#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;
const int N = 1005;
int f[N][N], s[N], t[N];
#define __(op)                                      \
  for (char &i : str_##op)                          \
    if (isspace(i) || ispunct(i)) {                 \
      if (!_.empty()) {                             \
        if (!id[_]) id[_] = op[++op##_len] = ++cnt; \
        else op[++op##_len] = id[_];                \
        _.clear();                                  \
      }                                             \
    } else _.push_back(i);                          \
  if (!_.empty()) {                                 \
    if (!id[_]) id[_] = op[++op##_len] = ++cnt;     \
    else op[++op##_len] = id[_];                    \
    _.clear();                                      \
  }
int main() {
  string str_s, str_t;
  int kase = 0;
  while (getline(cin, str_s) && getline(cin, str_t)) {
    ++kase;
    cout << (kase < 10 ? " " : "") << kase << ". ";
    if (str_s == "" || str_t == "") {
      cout << "Blank!" << endl;
      continue;
    }
    map<string, int> id;
    int cnt = 0, s_len = 0, t_len = 0;
    memset(f, 0, sizeof(f));
    string _;
    __(s);
    __(t);
    int ans = 0;
    for (int i = 1; i <= s_len; ++i)
      for (int j = 1; j <= t_len; ++j) {
        if (s[i] == t[j]) f[i][j] = f[i - 1][j - 1] + 1;
        else f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        ans = max(ans, f[i][j]);
      }
    cout << "Length of longest match: " << ans << endl;
  }
  return 0;
}
