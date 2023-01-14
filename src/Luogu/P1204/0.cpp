#include <bits/stdc++.h>
using namespace std;
int c[1000005];
int main() {
  int s = 2e9, e = -2e9;
  int n, a, b, f = 1, t[2] = {0}, ns;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a, &b);
    c[a]++;
    c[b]--;
    s = min(s, a);
    e = max(e, b - 1);
  }
  ns = s;
  int nc;
  ++e;
  for (int i = s; i <= e; i++) {
    c[i] = c[i - 1] + c[i];
    nc = c[i] == 0 ? 0 : 1;
    if (nc != f || i == e) {
      t[f] = max(t[f], i - ns);
      ns = i;
      f = 1 - f;
    }
  }
  printf("%d %d", t[1], t[0]);
  return 0;
}
