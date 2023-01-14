#include <bits/stdc++.h>
using namespace std;
int main() {
  char s[10], u[10];
  scanf("%s", &s);
  scanf("%s", &u);
  int nums = 1, numu = 1;
  int lens = strlen(s), lenu = strlen(u);
  for (int i = 0; i < lens; i++) nums *= s[i] - 64;
  for (int i = 0; i < lenu; i++) numu *= u[i] - 64;
  if (nums % 47 == numu % 47) cout << "GO";
  else cout << "STAY";
  return 0;
}
