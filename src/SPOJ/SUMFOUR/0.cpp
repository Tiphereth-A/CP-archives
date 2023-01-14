#include <bits/stdc++.h>
using namespace std;
int a[4001], b[4001], c[4001], d[4001], t[16000001], tot, ans;
namespace ae86 {
const int bufl = 1 << 15;
char buf[bufl], *s = buf, *t = buf;
int fetch() {
  if (s == t) {
    t = (s = buf) + fread(buf, 1, bufl, stdin);
    if (s == t) return EOF;
  }
  return *s++;
}
int read() {
  int a = 0, b = 1, c = fetch();
  while (!isdigit(c)) b ^= c == '-', c = fetch();
  while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
  return b ? a : -a;
}
}  // namespace ae86
using ae86::read;
int main() {
  int n = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    b[i] = read();
    c[i] = read();
    d[i] = read();
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) t[++tot] = a[i] + b[j];
  sort(t + 1, t + tot + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      auto &&p = equal_range(t + 1, t + tot + 1, -(c[i] + d[j]));
      ans += p.second - p.first;
    }
  printf("%d\n", ans);
  return 0;
}
