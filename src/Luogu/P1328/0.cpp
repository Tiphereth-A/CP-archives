#include <bits/stdc++.h>
#define MAXN 210
using namespace std;
const int f[5][5] = {{0, 0, 1, 1, 0},
                     {1, 0, 0, 1, 0},
                     {0, 1, 0, 0, 1},
                     {0, 0, 1, 0, 1},
                     {1, 1, 0, 0, 0}};
int a[MAXN], b[MAXN];
int main() {
  int n, na, nb, aa = 0, bb = 0;
  cin >> n >> na >> nb;
  for (int i = 0; i < na; i++) cin >> a[i];
  for (int i = 0; i < nb; i++) cin >> b[i];
  for (int i = 0; i < n; i++) {
    aa += f[a[i % na]][b[i % nb]];
    bb += f[b[i % nb]][a[i % na]];
  }
  cout << aa << ' ' << bb;
  return 0;
}
