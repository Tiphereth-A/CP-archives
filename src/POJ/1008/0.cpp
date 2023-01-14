#include <cstdio>
#include <cstring>
const char c[20][20] = {"pop",
                        "no",
                        "zip",
                        "zotz",
                        "tzec",
                        "xul",
                        "yoxkin",
                        "mol",
                        "chen",
                        "yax",
                        "zac",
                        "ceh",
                        "mac",
                        "kankin",
                        "muan",
                        "pax",
                        "koyab",
                        "cumhu",
                        "uayet"};
const char str[25][20] = {"imix",  "ik",    "akbal", "kan",   "chicchan",
                          "cimi",  "manik", "lamat", "muluk", "ok",
                          "chuen", "eb",    "ben",   "ix",    "mem",
                          "cib",   "caban", "eznab", "canac", "ahau"};
char s[100];
int f() {
  for (int i = 0; i < 19; i++)
    if (strcmp(s, c[i]) == 0) return i;
  return 0;
}
int main() {
  int _;
  scanf("%d", &_);
  printf("%d\n", _);
  while (_--) {
    int day, year;
    scanf("%d. %s %d", &day, s, &year);
    int __ = year * 365 + f() * 20 + day;
    year = __ / 260;
    strcpy(s, str[__ % 20]);
    day = (__ % 13) + 1;
    printf("%d %s %d\n", day, s, year);
  }
  return 0;
}
