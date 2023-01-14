#include <cstdio>
#include <cstring>
int find(bool &ans) {
  int wl, dl, wr, dr;
  scanf("%d%d%d%d", &wl, &dl, &wr, &dr);
  if (!wl) wl = find(ans);
  if (!wr) wr = find(ans);
  if (wl * dl != wr * dr) ans = false;
  return wl + wr;
}
int main() {
  int n;
  bool f = false;
  scanf("%d", &n);
  while (n--) {
    f = f ? puts("") : 1;
    bool ans = 1;
    find(ans);
    puts(ans ? "YES" : "NO");
  }
  return 0;
}
