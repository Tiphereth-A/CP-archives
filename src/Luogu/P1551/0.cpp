#include <bits/stdc++.h>
#define M 5005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define gi getint
#define gc getchar
using namespace std;
int pre[M];
int getint() {
  int t = 0;
  char c = gc();
  while (c < 48 || c > 57) c = gc();
  while (c >= 48 && c <= 57) {
    t = (t << 3) + (t << 1) + (c ^ 48);
    c = gc();
  }
  return t;
}
int find(int x) {
  int a = x, b = x, c;
  while (a != pre[a]) a = pre[a];
  while (b != pre[b]) {
    c = pre[b];
    pre[b] = a;
    b = c;
  }
  return a;
}
void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (fx != fy) pre[fx] = fy;
}
int main() {
  int n = gi(), m = gi(), p = gi();
  _for(i, 1, n) pre[i] = i;
  while (m--) {
    int x = gi(), y = gi();
    merge(x, y);
  }
  while (p--) {
    int x = gi(), y = gi();
    int fx = find(x), fy = find(y);
    if (fx == fy) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
