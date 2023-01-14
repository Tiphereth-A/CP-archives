#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 1e4 + 5;
int n, k;
struct node {
  int l, time;
  bool operator<(const node &oth) const { return l > oth.l; }
} task[N];
int f[N];
int main() {
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) cin >> task[i].l >> task[i].time;
  std::sort(task + 1, task + k + 1);
  int j = 1;
  for (int i = n; i; --i) {
    if (i != task[j].l) f[i] = f[i + 1] + 1;
    else
      while (task[j].l == i) f[i] = std::max(f[i], f[i + task[j++].time]);
  }
  cout << f[1];
  return 0;
}
