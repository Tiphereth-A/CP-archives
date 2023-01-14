#include <bits/stdc++.h>
using namespace std;
int n, a[10];
int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  if (prev_permutation(a, a + n))
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
  else cout << "ERROR";
  return 0;
}
