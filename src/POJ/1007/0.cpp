#include <algorithm>
#include <cstdio>
int l;
struct Node {
  char s[55];
  int val;
  bool operator<(const Node &rhs) const { return val < rhs.val; }
  void calc() {
    int a = 0, g = 0, c = 0, t = 0;
    for (int i = l - 1; ~i; --i) switch (s[i]) {
        case 'A': ++a; break;
        case 'C':
          ++c;
          val += a;
          break;
        case 'G':
          ++g;
          val += a + c;
          break;
        case 'T':
          ++t;
          val += a + c + g;
          break;
      }
  }
} a[105];
int main() {
  int cnt;
  scanf("%d%d", &l, &cnt);
  for (int i = 0; i < cnt; ++i) {
    scanf("%s", a[i].s);
    a[i].calc();
  }
  std::sort(a, a + cnt);
  for (int i = 0; i != cnt; ++i) puts(a[i].s);
  return 0;
}
