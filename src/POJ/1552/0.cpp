#include <cstdio>
#include <cstring>
bool vis[100];
int main() {
  int _ = 0;
  while (scanf("%d", &_) && ~_) {
    if (_) {
      vis[_] = 1;
    } else {
      for (int i = 98; i; i -= 2) { _ += vis[i] && vis[i / 2]; }
      printf("%d\n", _);
      memset(vis, 0, sizeof(vis));
    }
  }
}
