#include <bits/stdc++.h>
#define dec(i) (--(i))
#define int long long
using namespace std;
#define WW(i) (1 << (i))
void Solve() {
  int n, k;
  int Sum = 0, tot = 0;
  cin >> n >> k;
  vector<int> A(n), B(k);
  for (int i = 0; i < n; ++i) cin >> A[i], tot += A[i];
  for (int i = 0; i < k; ++i) cin >> B[i], Sum += B[i] * WW(i);
  int l = 0, r = Sum / tot, Mid, Ans = 0;
  while (r >= l) {
    int Mid = (r + l) >> 1;
    auto Pd = [&](int x) -> bool {
      vector<int> C(n), D(k);
      priority_queue<int> Q;
      for (int i = 0; i < n; ++i) Q.push(A[i] * x);
      D = B;
      for (int i = k - 1; ~i; --i) {
        while (!Q.empty() && D[i] && WW(i) >= Q.top()) {
          Q.pop();
          dec(D[i]);
        }
        while (!Q.empty() && D[i] && WW(i) < Q.top()) {
          int t = Q.top(), tt = t / WW(i), ttt = min(tt, D[i]);
          Q.pop();
          t -= ttt * WW(i), D[i] -= ttt;
          if (t) Q.push(t);
        }
        while (!Q.empty() && D[i] && WW(i) >= Q.top()) {
          Q.pop();
          dec(D[i]);
        }
      }
      if (Q.size()) return 0;
      return 1;
    };
    if (Pd(Mid)) Ans = Mid, l = Mid + 1;
    else r = Mid - 1;
  }
  cout << Ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) { Solve(); }
  return 0;
}
