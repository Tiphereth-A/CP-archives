#include <bits/stdc++.h>
using namespace std;
int a[2010], b[2010], c[2018];
char n[2001], m[2001];
int main() {
  int z;
  cin >> z >> n >> m;
  int l1 = strlen(n);
  int l2 = strlen(m);
  for (int i = 0; i < l1; i++)
    a[l1 - i] = (z > 10 && n[i] >= 'A') ? n[i] - 55 : n[i] - '0';
  for (int i = 0; i < l2; i++)
    b[l2 - i] = (z > 10 && m[i] >= 'A') ? m[i] - 55 : m[i] - '0';
  int x = 0, y = 0;
  while (x <= l1 || x <= l2) {
    ++x;
    c[x] = y + a[x] + b[x];
    y = c[x] / z;
    c[x] %= z;
  }
  while (c[x] == 0 && x > 1) --x;
  for (int i = x; i >= 1; --i) cout << (char)(c[i] + (c[i] < 10 ? '0' : 55));
  return 0;
}
