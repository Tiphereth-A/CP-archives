#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int x, y;
    cin >> x >> y;
    string op;
    cin >> op;
    int cnt[4] = {0};
    for (char ch : op) switch (ch) {
        case 'U': ++cnt[0]; break;
        case 'D': --cnt[1]; break;
        case 'R': ++cnt[2]; break;
        case 'L': --cnt[3]; break;
      }
    cout << ((cnt[1] <= y && cnt[0] >= y && cnt[3] <= x && cnt[2] >= x) ?
               "YES\n" :
               "NO\n");
  }
  return 0;
}
