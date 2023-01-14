#include <bits/stdc++.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int getint() {
  int t = 0;
  char c = gc();
  while (c < 48 || c > 57) c = gc();
  while (c >= 48 && c <= 57) {
    t = t * 10 + c - 48;
    c = gc();
  }
  return t;
}
int gcd(int a, int b) {
  if (a % b == 0) return b;
  return gcd(b, a % b);
}
int main() {
  int a = gi(), b = gi(), c = gi();
  int MAXN = max(a, max(b, c)), minn = min(a, min(b, c));
  int d = gcd(MAXN, minn);
  cout << minn / d << '/' << MAXN / d;
  return 0;
}
