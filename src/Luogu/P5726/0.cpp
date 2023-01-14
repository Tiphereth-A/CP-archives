#include <bits/stdc++.h>
using namespace std;
vector<int> a;
int main() {
  int n;
  cin >> n;
  for (int i = 1, _; i <= n; ++i) {
    cin >> _;
    a.push_back(_);
  }
  sort(a.begin(), a.end());
  if (n < 3) printf("0.00");
  else
    printf("%.2f",
           accumulate(a.begin() + 1, a.end() - 1, 0) * 1.0 / (a.size() - 2));
}
