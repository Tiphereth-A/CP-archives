#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 5;
long long cnt[N], sum[N];
int main() {
  int n;
  cin >> n;
  int max_a = 0;
  for (int i = 1, _; i <= n; ++i) {
    cin >> _;
    max_a = max(max_a, _);
    ++cnt[_];
  }
  for (int i = 1; i <= max_a; ++i) sum[i] = sum[i - 1] + i * cnt[i];
  for (int i = 1; i <= max_a; ++i) {
    long long l = sum[i - 1], r = sum[max_a] - sum[i];
    if ((l > 0 && l == r) || (cnt[i] > 1 && l == 0 && r == 0)) {
      cout << i;
      return 0;
    }
  }
  return 0;
}
