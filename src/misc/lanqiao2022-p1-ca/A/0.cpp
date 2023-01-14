#include <iostream>
using namespace std;
int main() {
  int n = 20, m = 22;
  int ans1 = 4, ans2 = n - 1 + n * (m - 1), ans3 = m - 1 + m * (n - 1);
  cout << ans1 + min(ans2, ans3);
}
