#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
struct t {
  int start, end;
} p[MAXN];
bool cmp(t a, t b) { return a.end < b.end; }
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> p[i].start >> p[i].end;
  sort(p + 1, p + n + 1, cmp);
  int pos = p[1].end, ans = 1;
  for (int i = 2; i <= n; i++) {
    if (p[i].start >= pos) {
      ans++;
      pos = p[i].end;
    }
  }
  cout << ans;
  return 0;
}
