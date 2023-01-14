#include <bits/stdc++.h>
using namespace std;
int dis[100], g[100][100];
int p, vis[100];
char r;
void ff(int x, int y, int w) {
  if (g[x][y] == 0) g[x][y] = g[y][x] = w;
  if (w < g[x][y]) g[x][y] = g[y][x] = w;
}
void gg() {
  int u, min;
  for (int i = 1; i <= 51; i++) {
    min = INT_MAX;
    for (int j = 1; j <= 51; j++)
      if (vis[j] == 0 && dis[j] < min) {
        min = dis[j];
        u = j;
      }
    vis[u] = 1;
    for (int v = 1; v <= 51; v++)
      if (dis[v] > dis[u] + g[u][v] && vis[v] == 0 && g[u][v] < INT_MAX)
        dis[v] = dis[u] + g[u][v];
  }
}
int main() {
  scanf("%d", &p);
  for (int i = 1; i <= 52; i++)
    for (int j = 1; j <= 51; j++) g[i][j] = INT_MAX;
  vis[52] = 1;
  for (int i = 1; i <= p; i++) {
    char x, y;
    int c;
    int xx, yy;
    scanf("\n%c %c %d", &x, &y, &c);
    if (x >= 'a' && x <= 'z') xx = x - 'a' + 1;
    else xx = x - 'A' + 27;
    if (y >= 'a' && y <= 'z') yy = y - 'a' + 1;
    else yy = y - 'A' + 27;
    ff(xx, yy, c);
  }
  for (int i = 1; i <= 51; i++) dis[i] = g[52][i];
  gg();
  int hh = INT_MAX, point;
  for (int i = 1; i <= 51; i++)
    if (dis[i] < hh && i >= 27) hh = dis[point = i];
  r = point - 27 + 'A';
  printf("%c %d\n", r, hh);
}
