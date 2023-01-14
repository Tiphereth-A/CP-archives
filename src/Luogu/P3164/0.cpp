#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<bool>> res;
template <size_t N>
void gauss_bitset(std::vector<std::bitset<N>> &mat) {
  for (size_t i = 0; i < std::min(mat.size(), N); ++i) {
    if (!mat[i][i]) {
      for (size_t j = i + 1; j < mat.size(); ++j)
        if (mat[j][i]) {
          std::swap(mat[j], mat[i]);
          break;
        }
    }
    if (!mat[i][i]) res[i / n][i % n] = 1;
    for (int64_t j = i + 1; j < mat.size(); ++j)
      if (mat[j][i]) mat[j] ^= mat[i];
  }
}
const pair<int, int> DIR[] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  cin >> m >> n;
  vector<bitset<1600>> mat(n * m);
  auto encode = [](int x, int y) { return x * n + y; };
  for (int i = 0, i_, j_; i < m; ++i)
    for (int j = 0; j < n; ++j)
      for (auto &&[dx, dy] : DIR) {
        i_ = i + dx;
        j_ = j + dy;
        if (i_ < 0 || j_ < 0 || i_ >= m || j_ >= n) continue;
        mat[encode(i, j)].set(encode(i_, j_));
      }
  res.resize(m, vector<bool>(n));
  gauss_bitset(mat);
  for (int i = n * m - 1; ~i; --i)
    for (int j = i + 1; j < n * m; ++j)
      res[i / n][i % n] = res[i / n][i % n] ^ (res[j / n][j % n] & mat[i][j]);
  for (auto &&i : res) {
    for (auto &&j : i) cout << j << ' ';
    cout << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
