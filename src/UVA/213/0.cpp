#include <cstdio>
#include <cstring>
char code[8][1 << 8];
char readchar() {
  for (;;) {
    char c = getchar();
    if (c != '\n' && c != '\r') return c;
  }
}
bool getcode() {
  memset(code, 0, sizeof(code));
  code[1][0] = readchar();
  for (int len = 2; len <= 7; ++len) {
    for (int j = 0; j < ((1 << len) - 1); ++j) {
      char ch = getchar();
      if (ch == EOF) return 0;
      if (ch == '\n' || ch == '\r') return 1;
      code[len][j] = ch;
    }
  }
  return true;
}
int getint(int l) {
  int ans = 0;
  while (l--) {
    int f = readchar();
    if (f != ' ') ans = (ans << 1) + f - '0';
    else ++l;
  }
  return ans;
}
int main() {
  while (getcode()) {
    for (;;) {
      int len = getint(3);
      if (!len) break;
      for (;;) {
        int now = getint(len);
        if (now == ((1 << len) - 1)) break;
        putchar(code[len][now]);
      }
    }
    putchar('\n');
  }
  return 0;
}
