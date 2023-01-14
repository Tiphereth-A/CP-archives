#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e3 + OFFSET;
int main() {
  i64 r, d, x;
  cin >> r >> d >> x;
  for (int i = 1; i <= 10; ++i) cout << (x = r * x - d) << endl;
  return 0;
}
