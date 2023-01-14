#include <bits/stdc++.h>
using f64 = double;
using u32 = uint32_t;
using u64 = uint64_t;
u64 pi(u64 n) {
  auto isqrt = [](u64 n) { return (u32)std::sqrt(n); };
  auto half = [](auto n) { return (n - 1) / 2; };
  auto divide = [](u64 n, u64 base) { return u64(f64(n) / (f64)base); };
  if (n <= 1) return 0;
  if (n == 2) return 1;
  const u32 lim = isqrt(n);
  u32 vsz = (lim + 1) >> 1;
  std::vector<u32> smalls(vsz);
  for (u32 cx = 0; cx < vsz; ++cx) smalls[cx] = cx;
  std::vector<u32> roughs(vsz);
  for (u32 cx = 0; cx < vsz; ++cx) roughs[cx] = (cx << 1 | 1);
  std::vector<u64> larges(vsz);
  for (u32 cx = 0; cx < vsz; ++cx) larges[cx] = (n / (cx << 1 | 1) - 1) >> 1;
  std::vector<bool> skips(lim + 1);
  u32 pCnt = 0;
  for (u32 p = 3; p <= lim; p += 2) {
    if (skips[p]) continue;
    u32 p2 = p * p;
    if (1LL * p2 * p2 > n) break;
    skips[p] = true;
    for (u32 cx = p2; cx <= lim; cx += (p << 1)) skips[cx] = true;
    u32 ns = 0;
    for (u32 cx = 0; cx < vsz; ++cx) {
      u32 cur = roughs[cx];
      if (skips[cur]) continue;
      u64 d = 1LL * cur * p;
      larges[ns] = larges[cx] -
                   (d <= lim ? larges[smalls[d >> 1] - pCnt] :
                               smalls[half(divide(n, d))]) +
                   pCnt;
      roughs[ns++] = cur;
    }
    vsz = ns;
    for (u32 cx = half(lim), cy = ((lim / p) - 1) | 1; cy >= p; cy -= 2) {
      u32 cur = smalls[cy >> 1] - pCnt;
      for (u32 cz = (cy * p) >> 1; cz <= cx; --cx) smalls[cx] -= cur;
    }
    ++pCnt;
  }
  larges[0] += 1LL * (vsz + ((pCnt - 1) << 1)) * (vsz - 1) >> 1;
  for (u32 cx = 1; cx < vsz; ++cx) larges[0] -= larges[cx];
  for (u32 cx = 1; cx < vsz; ++cx) {
    u32 q = roughs[cx];
    u64 m = n / q;
    u32 e = smalls[half(m / q)] - pCnt;
    if (e < cx + 1) break;
    u64 t = 0;
    for (u32 cy = cx + 1; cy <= e; ++cy)
      t += smalls[half(divide(m, roughs[cy]))];
    larges[0] += t - 1LL * (e - cx) * (pCnt + cx - 1);
  }
  return larges[0] + 1;
}
int main() {
  u64 n;
  std::cin >> n;
  std::cout << pi(n);
  return 0;
}
