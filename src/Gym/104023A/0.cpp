#include <bits/stdc++.h>
using namespace std;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  map<string, int> M;
  cin >> T;
  int tot = 0;
  for (int i = 1; i <= T; ++i)
    for (int j = 1; j <= 5; ++j) {
      string S;
      cin >> S;
      M[S] = 1;
    }
  int m;
  cin >> m;
  vector<int> cnt(6);
  for (int i = 1; i <= m; ++i) {
    string S;
    int opt;
    cin >> S >> opt;
    tot += M[S];
    ++cnt[opt];
  }
  int Min = cnt[1];
  for (int i = 2; i <= 5; ++i) { Min = min(Min, cnt[i]); }
  cout << min(Min, tot);
  return 0;
}
