#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
double lg[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  for (int i = 1; i < N; ++i) lg[i] = lg[i - 1] + log10(i);
  i64 n, _;
  cin >> n;
  while (n--) {
    cin >> _;
    cout << ((long long)lg[_] + 1) << '\n';
  }
  return 0;
}
