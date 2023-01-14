#include <bits/stdc++.h>
using namespace std;
long long a[100010];
void quicksort(int, int);
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a, a + n + 1);
  for (int i = 1; i <= n; i++) cout << a[i] << ' ';
  return 0;
}
