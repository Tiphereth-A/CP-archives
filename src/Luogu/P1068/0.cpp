#include <bits/stdc++.h>
using namespace std;
struct member {
  int num;
  int score;
} mem[5010];
bool cmp(const member &a, const member &b) {
  if (a.score > b.score) return 1;
  else if (a.score == b.score) {
    if (a.num < b.num) return 1;
  }
  return 0;
}
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> mem[i].num >> mem[i].score;
  sort(mem + 1, mem + n + 1, cmp);
  int p = floor(m * 1.5);
  int ans = mem[p].score;
  for (int i = p + 1; i <= n; i++)
    if (mem[i].score == ans) p++;
    else break;
  cout << ans << ' ' << p << endl;
  for (int i = 1; i <= p; i++)
    cout << mem[i].num << ' ' << mem[i].score << endl;
  return 0;
}
