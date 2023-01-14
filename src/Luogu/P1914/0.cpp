#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  char c[100];
  scanf("%d%s", &n, c);
  for (int j = 0; c[j] != '\0'; j++) putchar((c[j] - 'a' + n) % 26 + 'a');
  return 0;
}
