#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
struct node {
  int id, t;
  bool operator<(const node &a) const {
    return (this->t == a.t) ? (this->id < a.id) : (this->t < a.t);
  }
} p[1005];
int n;
long double ans;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    p[i].id = i;
    scanf("%d", &(p[i].t));
  }
  std::sort(p + 1, p + n + 1);
  _for(i, 1, n) {
    ans += (n - i) * p[i].t;
    printf("%d ", p[i].id);
  }
  printf("\n%.2Lf", ans / n);
}
