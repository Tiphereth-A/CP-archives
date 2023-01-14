#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
int tmp[100005], cnt;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cnt = 0;
    for (int l = 1; l <= n; l = n / (n / l) + 1) tmp[++cnt] = n / l;
    cout << cnt + 1 << endl << "0 ";
    for (int i = cnt; i; --i) cout << tmp[i] << " ";
    cout << endl;
  }
  return 0;
}
