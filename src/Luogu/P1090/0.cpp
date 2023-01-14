#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
int n;
std::priority_queue<u64, std::vector<u64>, std::greater<u64>> q;
int main() {
  cin >> n;
  for (int a, i = 1; i <= n; i++) {
    cin >> a;
    q.push(a);
  }
  u64 ans = 0;
  while (q.size() > 1) {
    u64 a = q.top();
    q.pop();
    u64 b = q.top();
    q.pop();
    ans += a + b;
    q.push(a + b);
  }
  cout << ans;
  return 0;
}
