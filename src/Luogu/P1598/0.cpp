#include <bits/stdc++.h>
char in[1001];
long long cnt[35];
long long max(long long x, long long y) { return x > y ? x : y; }
long long MAXN = 0;
int main() {
  for (int i = 0; i < 4; i++) {
    fgets(in, 1000, stdin);
    for (int j = 0; in[j]; j++)
      if (in[j] != ' ') ++cnt[in[j] - 'A' + 1];
  }
  for (int i = 1; i <= 26; ++i) MAXN = max(MAXN, cnt[i]);
  for (int i = MAXN; i; --i) {
    for (int j = 1; j <= 26; ++j) {
      if (cnt[j] >= i) putchar('*');
      else putchar(' ');
      if (j != 26) putchar(' ');
    }
    putchar('\n');
  }
  printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
}
