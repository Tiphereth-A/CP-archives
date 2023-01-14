#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct {
  int a, b, c, tot;
} a[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].a >> a[i].b >> a[i].c;
    a[i].tot = a[i].a + a[i].b + a[i].c;
  }
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      if (abs(a[i].a - a[j].a) <= 5 && abs(a[i].b - a[j].b) <= 5 &&
          abs(a[i].c - a[j].c) <= 5 && abs(a[i].tot - a[j].tot) <= 10)
        ++cnt;
  cout << cnt;
  return 0;
}
