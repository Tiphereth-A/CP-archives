#include <bits/stdc++.h>
using namespace std;
int l[105];
int main() {
  long long w, h, x, y;
  cin >> w >> h >> x >> y;
  cout << w * h / 2.0 << " " << (x * 2 == w && y * 2 == h);
  return 0;
}
