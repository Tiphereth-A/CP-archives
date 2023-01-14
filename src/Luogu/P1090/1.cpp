#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> a;
int main() {
  int n, ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int m;
    cin >> m;
    a.push(m);
  }
  for (int i = 1; i < n; i++) {
    int b = a.top();
    a.pop();
    int c = b + a.top();
    a.pop();
    ans += c;
    a.push(c);
  }
  cout << ans;
  return 0;
}
