#include <cstdio>
#define gc getchar
#define pc putchar
char c, s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int i;
int main() {
  while ((c = gc()) != EOF) {
    for (i = 1; s[i] && s[i] != c; i++);
    if (s[i]) pc(s[i - 1]);
    else pc(c);
  }
  return 0;
}
