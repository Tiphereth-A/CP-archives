#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
typedef unsigned int u32;
int main() {
  int t;
  cin >> t;
  while (t--) {
    u32 a, b;
    cin >> a >> b;
    cout << (((a + b) % 3 || std::max(a, b) > 2 * std::min(a, b)) ? "NO" :
                                                                    "YES")
         << endl;
  }
  return 0;
}
