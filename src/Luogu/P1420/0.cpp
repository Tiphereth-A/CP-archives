#include <bits/stdc++.h>
#define M 10005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int ans[M], num[M];
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
int main() {
  int n = gi();
  _for(i, 1, n) num[i] = gi();
  ans[1] = 1;
  _for(i, 2, n) {
    ans[i] = 1;
    if (num[i] == num[i - 1] + 1) ans[i] += ans[i - 1];
  }
  int t = 0;
  _for(i, 1, n) t = max(t, ans[i]);
  cout << t;
  return 0;
}
