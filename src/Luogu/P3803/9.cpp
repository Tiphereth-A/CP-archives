#include <bits/stdc++.h>
typedef std::complex<double> Comp;
const Comp I(0, 1);
const int MAX_N = 1 << 21;
Comp tmp[MAX_N], c[MAX_N];
void DFT(Comp *f, int n, int rev) {
  if (n == 1) return;
  for (int i = 0; i < n; ++i) tmp[i] = f[i];
  for (int i = 0; i < n; ++i) {
    if (i & 1) f[n / 2 + i / 2] = tmp[i];
    else f[i / 2] = tmp[i];
  }
  Comp *g = f, *h = f + n / 2;
  DFT(g, n / 2, rev), DFT(h, n / 2, rev);
  Comp cur(1, 0), step(cos(2 * M_PI / n), sin(2 * M_PI * rev / n));
  for (int k = 0; k < n / 2; ++k) {
    tmp[k] = g[k] + cur * h[k];
    tmp[k + n / 2] = g[k] - cur * h[k];
    cur *= step;
  }
  for (int i = 0; i < n; ++i) f[i] = tmp[i];
}
using namespace std;
int main() {
  unsigned n, m;
  cin >> n >> m;
  unsigned N = bit_ceil(n + m + 2);
  for (unsigned i = 0, x; i <= n; ++i) (cin >> x), c[i].real(x);
  for (unsigned i = 0, x; i <= m; ++i) (cin >> x), c[i].imag(x);
  DFT(c, N, 1);
  for (unsigned i = 0; i < N; ++i) c[i] *= c[i];
  DFT(c, N, -1);
  cout << fixed << setprecision(0);
  for (unsigned i = 0; i <= n + m; ++i)
    cout << (c[i].imag() + N * .5) / (2 * N) << " \n"[i == n + m];
  return 0;
}
