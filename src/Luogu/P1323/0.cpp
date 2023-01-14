#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> q;
string ans, s1;
int k, m, i;
int main() {
  cin >> k >> m;
  q.push(1);
  while (!q.empty() && i < k) {
    int p = q.top();
    q.pop();
    q.push(p * 2 + 1);
    q.push(p * 4 + 5);
    stringstream s;
    s << p;
    s >> s1;
    ans += s1;
    ++i;
  }
  cout << ans << endl;
  for (int i = 1; i <= m; i++) {
    int j, l = ans.size();
    for (j = 0; j < l - 1; j++)
      if (ans[j] < ans[j + 1]) {
        ans.erase(j, 1);
        break;
      }
    if (j == l - 2) ans.erase(l - 1, 1);
  }
  cout << ans;
  return 0;
}
