#include <iostream>
using namespace std;
int main() {
  i64 p, e, i, d;
  int kase = 0;
  while ((cin >> p >> e >> i >> d) && (~p || ~e || ~i || ~d)) {
    i64 ans = (p * 5544 + e * 14421 + i * 1288) % 21252 - d;
    if (ans <= 0) ans += 21252;
    cout << "Case " << ++kase << ": the next triple peak occurs in " << ans
         << " days." << endl;
  }
}
