#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  sort(a + 1, a + n + 1, greater<int>());
  for (int l = 1; l <= n; ++l) {
    if (a[l + 1] >= l + 1) continue;
    int r = l;
    for (; a[r + 1] == l; ++r);
    puts(((r - l) | (a[l] - l)) & 1 ? "First" : "Second");
    break;
  }
  return 0;
}
