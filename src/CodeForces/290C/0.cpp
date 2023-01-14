#include <bits/stdc++.h>
using namespace std;
int main() {
  double tux, pur, foo = 0, bar = 0, baz = 0, quz = 1;
  cin >> tux;
  for (int i = 1; i <= tux; ++i) {
    cin >> pur;
    foo += pur;
    ++bar;
    if (foo * quz > baz * bar) {
      baz = foo;
      quz = bar;
    }
  }
  cout << fixed << setprecision(6) << baz / quz;
  return 0;
}
