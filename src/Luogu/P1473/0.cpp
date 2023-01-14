#include <bits/stdc++.h>
using namespace std;
int n, sz[20], ss;
char sym[20];
void f(int k, int s, int q, char c) {
  if (k == n) {
    s = c == '+' ? s + q : s - q;
    if (s == 0) {
      ss++;
      cout << "1";
      for (int i = 1; i < n; i++) cout << sym[i] << sz[i];
      cout << " " << ss << endl;
    }
  } else {
    sym[k] = ' ';
    f(k + 1, s, q * 10 + sz[k], c);
    sym[k] = '+';
    if (c == '+') f(k + 1, s + q, sz[k], '+');
    else f(k + 1, s - q, sz[k], '+');
    sym[k] = '-';
    if (c == '+') f(k + 1, s + q, sz[k], '-');
    else f(k + 1, s - q, sz[k], '-');
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) sz[i] = i + 1;
  f(1, 0, 1, '+');
  return 0;
}
