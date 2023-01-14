#include <bits/stdc++.h>
using namespace std;
const int a[5] = {1, 3, 5, 7, 9};
int n;
bool prime(int x) {
  if (x == 1) return 0;
  if (x == 2) return 1;
  for (int i = 2; i <= sqrt(x); i++)
    if (x % i == 0) return 0;
  return 1;
}
void dfs(int k, int sum) {
  if (sum == n) {
    cout << k << endl;
    return;
  } else
    for (int i = 0, p; i < 5; i++) {
      p = k * 10 + a[i];
      if (prime(p)) dfs(p, sum + 1);
    }
}
int main() {
  cin >> n;
  dfs(2, 1);
  dfs(3, 1);
  dfs(5, 1);
  dfs(7, 1);
  return 0;
}
