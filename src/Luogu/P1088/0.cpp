#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < k; i++) next_permutation(a, a + n);
  for (int i = 0; i < n; i++) cout << a[i] << ' ';
  return 0;
}
