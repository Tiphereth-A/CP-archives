#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main() {
  ll n, k, c, i;
  cin >> n >> k;
  for (i = n;; i += (i & -i)) {
    c = 0;
    for (int j = 0; j < 64; j++)
      if (i & (1LL << j)) c++;
    if (c <= k) break;
  }
  cout << i - n;
  return 0;
}
