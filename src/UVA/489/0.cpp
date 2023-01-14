#include <cstdio>
#include <cstring>
int left, chance, lensys;
char sys[110], user[110];
bool win, lose;
void guess(char c) {
  bool f = true;
  for (int i = 0; i < lensys; ++i)
    if (sys[i] == c) {
      --left;
      sys[i] = ' ';
      f = false;
    }
  if (f) --chance;
  if (!chance) lose = true;
  if (!left) win = true;
}
int main() {
  int rnd;
  while (scanf("%d%s%s", &rnd, sys, user) == 3 && ~rnd) {
    printf("Round %d\n", rnd);
    win = lose = false;
    left = strlen(sys);
    lensys = strlen(sys);
    chance = 7;
    for (int i = 0, len = strlen(user); i < len; ++i) {
      guess(user[i]);
      if (win || lose) break;
    }
    if (win) printf("You win.\n");
    else if (lose) printf("You lose.\n");
    else printf("You chickened out.\n");
  }
  return 0;
}
