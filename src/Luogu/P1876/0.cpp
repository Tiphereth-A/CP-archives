#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  n = sqrt(n);
  for (int i = 1; i <= n; i++) printf("%d ", i * i);
  return 0;
}
