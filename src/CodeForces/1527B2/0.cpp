#include <bits/stdc++.h>
using namespace std;
#define _all(a) (a).begin(), (a).end()
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    string s1;
    cin >> n >> s1;
    string s2 = s1;
    reverse(_all(s2));
    int cnt = accumulate(_all(s1), 0, [](const int &i, const char &ch) {
      return i + (ch == '0');
    });
    cout << (s1 == s2 ?
               ((cnt % 2) && (cnt > 1) ? "ALICE" : "BOB") :
               ((n % 2) && (s1[n / 2] == '0') && (cnt == 2) ? "DRAW" : "ALICE"))
         << '\n';
  }
  return 0;
}
