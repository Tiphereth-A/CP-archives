#include <cctype>
#include <cstdio>
#include <cstring>
const char *rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char *msg[] = {"not a palindrome",
                     "a regular palindrome",
                     "a mirrored string",
                     "a mirrored palindrome"};
char s[50];
char re(char ch) { return isalpha(ch) ? rev[ch - 'A'] : rev[ch - '0' + 25]; }
int main() {
  while (scanf("%s", s) == 1) {
    int f = 3, len = strlen(s);
    for (int i = 0; i < (len + 1) >> 1; ++i) {
      if (s[i] != s[len - i - 1]) f = 2;
      if (re(s[i]) != s[len - i - 1]) f &= 1;
    }
    printf("%s -- is %s.\n\n", s, msg[f]);
  }
  return 0;
}
