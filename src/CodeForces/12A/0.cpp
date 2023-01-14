#include <bits/stdc++.h>
using namespace std;
string s1, s2, s3, str;
int main() {
  cin >> s1 >> s2 >> s3;
  str = s1 + s2 + s3;
  for (int i = 0; i < 4; ++i)
    if (str[i] != str[8 - i]) {
      printf("NO\n");
      return 0;
    }
  printf("YES\n");
}
