#include <bits/stdc++.h>
using namespace std;
int main() {
  int w;
  cin >> w;
  if ((w & 1) || (w == 2)) cout << "NO";
  else cout << "YES";
  return 0;
}
