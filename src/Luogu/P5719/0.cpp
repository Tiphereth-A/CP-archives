#include <bits/stdc++.h>
using namespace std;
vector<int> a, b;
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) (i % k ? b : a).push_back(i);
  printf("%.1lf %.1lf\n",
         accumulate(a.begin(), a.end(), 0) * 1.0 / a.size(),
         accumulate(b.begin(), b.end(), 0) * 1.0 / b.size());
  return 0;
}
