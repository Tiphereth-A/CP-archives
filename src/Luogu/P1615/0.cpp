#include <bits/stdc++.h>
using namespace std;
long long a, b, c, x, y, z, t;
char m;
int main() {
  cin >> a >> m >> b >> m >> c >> x >> m >> y >> m >> z >> t;
  cout << ((x - a) * 3600 + (y - b) * 60 + (z - c)) * t;
  return 0;
}
