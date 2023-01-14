#include <bits/stdc++.h>
using namespace std;
int p1, p2, p3, pos = -1, bit;
string s, ins;
bool comp(char a, char b) {
  if (a < b && (((a >= '0' && a <= '9') && (b >= '0' && b <= '9')) ||
                ((a >= 'A' && a <= 'z') && (b >= 'A' && b <= 'z'))))
    return 1;
  else return 0;
}
int main() {
  cin >> p1 >> p2 >> p3;
  cin >> s;
  while (1) {
    pos = s.find('-', pos + 1);
    if (pos == string::npos) break;
    char a = s[pos - 1];
    char b = s[pos + 1];
    if (comp(a, b) == 1) {
      bit = ((b - a - 1) * p2) + 1;
      ins = a;
      for (int i = a + 1; i < b; i++)
        for (int k = (i - a - 1) * p2 + 1; k <= (i - a) * p2; k++) ins += i;
      ins += b;
      if (p1 == 1) {
      } else if (p1 == 2) {
        for (int i = 1; i <= bit - 1; i++)
          if (ins[i] >= 'a' && ins[i] <= 'z') ins[i] -= 32;
      } else if (p1 == 3) {
        ins = a;
        for (int i = a + 1; i < b; i++)
          for (int k = (i - a - 1) * p2 + 1; k <= (i - a) * p2; k++)
            ins += '\*';
        ins += b;
      }
      string p3s = ins;
      if (p3 == 2)
        for (int i = 1; i <= bit - 1; i++) ins[bit - i] = p3s[i];
      s.replace(pos - 1, 3, ins);
    } else continue;
  }
  cout << s;
  return 0;
}
