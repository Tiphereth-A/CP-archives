#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _gc getchar
#define _err puts("This puzzle has no final configuration.")
#define _mem(a) memset(a, 0, sizeof(a))
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
char map[7][7];
bool legel(int i, int j) { return i > 0 && i < 6 && j > 0 && j < 6; }
void output() {
  _for(i, 1, 5) {
    _for(j, 1, 4) printf("%c ", map[i][j]);
    printf("%c\n", map[i][5]);
  }
}
int main() {
  char c;
  int kase = 0;
  int nowi = -1, nowj = -1;
  while (!feof(stdin)) {
    int nowi = -1, nowj = -1;
    _mem(map);
    _for(i, 1, 5) {
      _for(j, 1, 5) {
        map[i][j] = (c = _gc());
        if (c == ' ') {
          nowi = i;
          nowj = j;
        }
        if (c == 'Z') return 0;
      }
      while (_gc() != '\n');
    }
    if (kase) puts("");
    printf("Puzzle #%d:\n", ++kase);
    int flag = 0;
    while (c != '0' && ~(c = _gc())) {
      switch (c) {
        case '\r':
        case '\n': break;
        case 'A':
          if (flag) break;
          if (legel(nowi - 1, nowj)) {
            Swap(map[nowi - 1][nowj], map[nowi][nowj]);
            nowi--;
          } else {
            _err;
            flag = 1;
          }
          break;
        case 'B':
          if (flag) break;
          if (legel(nowi + 1, nowj)) {
            Swap(map[nowi + 1][nowj], map[nowi][nowj]);
            nowi++;
          } else {
            _err;
            flag = 1;
          }
          break;
        case 'L':
          if (flag) break;
          if (legel(nowi, nowj - 1)) {
            Swap(map[nowi][nowj - 1], map[nowi][nowj]);
            nowj--;
          } else {
            _err;
            flag = 1;
          }
          break;
        case 'R':
          if (flag) break;
          if (legel(nowi, nowj + 1)) {
            Swap(map[nowi][nowj + 1], map[nowi][nowj]);
            nowj++;
          } else {
            _err;
            flag = 1;
          }
          break;
        case '0':
          if (flag) break;
          output();
          break;
        default:
          if (flag) break;
          _err;
          flag = 1;
      }
    }
    while (_gc() != '\n');
  }
  return 0;
}
