#include <bits/stdc++.h>
using namespace std;
const string base = "abcdefghijklmnopqrstuvwxyz";
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    long long n, a, b;
    cin >> n >> a >> b;
    string s;
    for (int i = 0; i <= n; i += b) s.append(base.substr(0, b));
    s.resize(n);
    cout << s << endl;
  }
  return 0;
}
