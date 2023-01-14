#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int k;
int main() {
  bool f = 1;
  cin >> k;
  _for(i, 10000, 30000)
    if ((i / 100 % k == 0) && (i / 10 % 1000 % k == 0) && (i % 1000 % k == 0))
      printf("%d\n", i), f = 0;
  if (f) cout << "No";
  return 0;
}
