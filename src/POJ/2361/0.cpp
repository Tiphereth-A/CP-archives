#include <cstdio>
char maps[3][3];
bool ok(char c) {
  if (maps[0][0] == c && maps[0][1] == c && maps[0][2] == c) return 1;
  if (maps[0][0] == c && maps[1][0] == c && maps[2][0] == c) return 1;
  if (maps[0][0] == c && maps[1][1] == c && maps[2][2] == c) return 1;
  if (maps[1][0] == c && maps[1][1] == c && maps[1][2] == c) return 1;
  if (maps[2][0] == c && maps[2][1] == c && maps[2][2] == c) return 1;
  if (maps[0][1] == c && maps[1][1] == c && maps[2][1] == c) return 1;
  if (maps[0][2] == c && maps[1][2] == c && maps[2][2] == c) return 1;
  if (maps[0][2] == c && maps[1][1] == c && maps[2][0] == c) return 1;
  return 0;
}
int main() {
  int n;
  while (~scanf("%d", &n))
    while (n--) {
      for (int i = 0; i < 3; ++i) scanf("%s", maps[i]);
      bool win_x = ok('X'), win_o = ok('O');
      int cnt_x = 0, cnt_o = 0;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
          cnt_x += (maps[i][j] == 'X');
          cnt_o += (maps[i][j] == 'O');
        }
      puts((cnt_x == cnt_o + 1 && win_x && !win_o ||
            cnt_x == cnt_o && win_o && !win_x ||
            (cnt_x == cnt_o || cnt_x == cnt_o + 1) && !win_x && !win_o) ?
             "yes" :
             "no");
    }
  return 0;
}
