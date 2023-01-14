#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
int n;
struct bt {
  char data, l, r;
} f[1000];
void print(char data) {
  if (data == '*') return;
  _for(i, 1, n) {
    if (f[i].data == data) {
      cout << f[i].data;
      print(f[i].l);
      print(f[i].r);
      return;
    }
  }
}
int main() {
  cin >> n;
  _for(i, 1, n) cin >> f[i].data >> f[i].l >> f[i].r;
  print(f[1].data);
  return 0;
}
