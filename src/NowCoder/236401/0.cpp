#include <bits/stdc++.h>
using namespace std;
char s[20];
int main() {
  while (fgets(s, 19, stdin) != nullptr) {
    int cnt = 0;
    for (char ch : s) cnt += ch == ':';
    int a = 0, b = 0, c = 0;
    double d = 0;
    if (cnt == 1) sscanf(s, "%d:%d %lfx", &b, &c, &d);
    else sscanf(s, "%d:%d:%d %lfx", &a, &b, &c, &d);
    int h = round(((a * 60 + b) * 60 + c) / d);
    if (h < 60) {
      printf("0:%02d\n", h);
      continue;
    }
    if (h < 3600) {
      printf("%d:%02d\n", h / 60, h % 60);
      continue;
    }
    printf("%d:%02d:%02d\n", h / 3600, h / 60 % 60, h % 60);
  }
  return 0;
}
