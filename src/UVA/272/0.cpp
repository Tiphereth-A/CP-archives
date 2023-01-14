#include <bits/stdc++.h>
using namespace std;
int main() {
  int f = 1;
  char c;
  while ((c = getchar()) != EOF)
    if (c == '"') {
      cout << (f ? "``" : "''");
      f = !f;
    } else cout << c;
  return 0;
}
