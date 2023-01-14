#include <bits/stdc++.h>
const int N = 2e5 + 5;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
i64 id[N], win[N], lose[N];
i64 rank[N], data[N];
int n, r, q, cnt_win, cnt_lose;
bool cmp(int a, int b) {
  return (rank[a] == rank[b]) ? (a < b) : (rank[a] > rank[b]);
}
void merge() {
  int i = 1, j = 1, cnt = 0;
  while (i <= cnt_win && j <= cnt_lose)
    id[++cnt] = cmp(win[i], lose[j]) ? win[i++] : lose[j++];
  while (i <= cnt_win) id[++cnt] = win[i++];
  while (j <= cnt_lose) id[++cnt] = lose[j++];
}
int main() {
  scanf("%d%d%d", &n, &r, &q);
  n <<= 1;
  _for(i, 1, n) {
    scanf("%lld", rank + i);
    id[i] = i;
  }
  _for(i, 1, n) scanf("%lld", data + i);
  std::sort(id + 1, id + n + 1, [](int a, int b) {
    return (rank[a] == rank[b]) ? (a < b) : (rank[a] > rank[b]);
  });
  while (r--) {
    cnt_win = cnt_lose = 0;
    for (int i = 1; i <= n; i += 2) {
      if (data[id[i]] > data[id[i + 1]]) {
        ++rank[win[++cnt_win] = id[i]];
        lose[++cnt_lose] = id[i + 1];
      } else {
        ++rank[win[++cnt_win] = id[i + 1]];
        lose[++cnt_lose] = id[i];
      }
    }
    merge();
  }
  printf("%lld", id[q]);
  return 0;
}
