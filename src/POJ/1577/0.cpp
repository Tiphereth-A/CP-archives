#include <cctype>
#include <cstdio>
#include <cstring>
const int N = 105;
struct Node {
  char ch;
  int l, r;
} bst[N];
int cnt_bst = 1;
void insert(char ch) {
  int fa = 1;
  if (!bst[fa].ch) {
    bst[fa].ch = ch;
    return;
  }
  while (1) {
    if (bst[fa].ch < ch) {
      if (!bst[fa].r) {
        bst[bst[fa].r = ++cnt_bst].ch = ch;
        return;
      } else fa = bst[fa].r;
    } else {
      if (!bst[fa].l) {
        bst[bst[fa].l = ++cnt_bst].ch = ch;
        return;
      } else fa = bst[fa].l;
    }
  }
}
void print(int idx) {
  if (!idx) return;
  putchar(bst[idx].ch);
  print(bst[idx].l);
  print(bst[idx].r);
}
char _[N], ch;
int cnt;
int main() {
  while ((ch = getchar()) && !feof(stdin)) {
    if (isalpha(ch)) _[++cnt] = ch;
    else if (ch == '*' || ch == '$') {
      for (int i = cnt; i; --i) insert(_[i]);
      print(1);
      puts("");
      cnt = 0;
      cnt_bst = 1;
      memset(bst, 0, sizeof(bst));
    }
  }
}
