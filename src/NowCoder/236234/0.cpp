#include <bits/stdc++.h>
using namespace std;
const int ans[5][11] = {
  {},
  {0, 7, 42, 252, 1512, 9072, 54432, 326592, 1959552, 11757312, 70543872},
  {0,
   42,
   1302,
   40362,
   1251222,
   38787882,
   202424335,
   275154343,
   529784577,
   423321775,
   122974934},
  {0,
   252,
   40362,
   6464682,
   35432335,
   842671407,
   616154088,
   437759359,
   327032958,
   134696199,
   101364960},
  {0,
   1512,
   1251222,
   35432335,
   858748060,
   475588928,
   441649817,
   820056146,
   163409120,
   542623454,
   754486763}};
auto solve() -> void {
  uint32_t n, m;
  cin >> n >> m;
  cout << ans[n][m];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
