#include <bits/stdc++.h>
using namespace std;
using std::numbers::pi;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  valarray<complex<double>> p(n), omega(n);
  _for(i, 0, n - 1) omega[i] = polar(1.0, 2 * pi * i / n);
  _for(i, 0, n - 1, x, y) {
    cin >> x >> y;
    p[i] = {x, y};
  }
  p -= p.sum() / ((double)p.size() + 0i);
  cout << fixed << setprecision(12)
       << (-norm((p * omega).sum()) + norm((p * (omega.apply(conj))).sum())) *
            sin(2 * pi / n) / n;
  return 0;
}
