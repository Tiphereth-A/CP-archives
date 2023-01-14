#include <bits/stdc++.h>
using namespace std;
int ans = 0;
bool f[10010];
void cnt(int line, int cross = 0) {
  if (!line) {
    if (!f[cross]) ans++;
    f[cross] = 1;
    return;
  }
  for (int i = line; i; --i) cnt(line - i, i * (line - i) + cross);
}
int main() {
  int n;
  cin >> n;
  cnt(n);
  cout << ans;
}
