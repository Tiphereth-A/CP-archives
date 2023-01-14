#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
template <typename T>
void read(T &x) {
  x = 0;
  char ch;
  while (ch = getc(), !isdigit(ch));
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
}
}  // namespace FastIO
using FastIO::read;
const int N = 1e6 + 5;
int n, c[N], ans[N];
template <typename T>
class BIT {
private:
  T tree[N];
  std::size_t _n = N - 1;
  std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }
  bool getmax(T &a, T b) { return a < b ? a = b, 1 : 0; }

public:
  BIT() { memset(tree, 0, sizeof(tree)); }
  void modify(std::size_t pos, T val = 1) {
    for (; pos <= _n; pos += lowbit(pos)) getmax(tree[pos], val);
  }
  T query(std::size_t pos) {
    T ret = 0;
    for (; pos; pos = (std::ptrdiff_t)pos - lowbit(pos)) getmax(ret, tree[pos]);
    return ret;
  }
  void clear(std::size_t n) { memset(tree, 0, sizeof(T) * ((_n = n) + 1)); }
};
BIT<int> tr;
int main() {
  int _t;
  read(_t);
  while (_t--) {
    read(n);
    tr.clear(n);
    for (int i = 1; i <= n; ++i) read(c[i]);
    for (int i = n; i; --i) tr.modify(c[i], ans[i] = tr.query(c[i]) + 1);
    printf("%d\n", tr.query(n));
    for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
  }
  return 0;
}
