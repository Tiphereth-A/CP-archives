#include <bits/stdc++.h>
#define M 10005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
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
  int a = x;
  while (a != pre[a]) a = pre[a];
  int b = x, c;
  while (b != a) {
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
  int n, m;
  n = gi();
  m = gi();
  _for(i, 1, n) pre[i] = i;
  _for(i, 1, m) {
    int z, x, y;
    z = gi();
    x = gi();
    y = gi();
    if (z == 1) merge(x, y);
    else {
      int fx = find(x), fy = find(y);
      if (fx == fy) printf("Y\n");
      else printf("N\n");
    }
  }
  return 0;
}
