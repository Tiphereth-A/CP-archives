#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> a;
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int main() {
  int n;
  while (cin >> n) {
    int ans = 0;
    a.clear();
    if (n == 0) break;
    a.push_back(n);
    while (cin >> n) {
      if (n == 0) break;
      a.push_back(n);
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < a.size(); ++i) ans = gcd(ans, a[i] - a[i - 1]);
    cout << ans << endl;
  }
}
