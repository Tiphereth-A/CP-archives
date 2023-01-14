#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define M 10005
const int INF = 0x7fffffff;
int num[M], n, c, m, slen, pos = 1;
std::stack<int> sta;
int main() {
  scanf("%d%d", &n, &c);
  _for(i, 1, n) scanf("%d", num + i);
  while (sta.size() + m < n) {
    slen = sta.size();
    int minn = INF, l = pos, len = c - slen;
    for (int j = l; j < l + len && j <= n; j++) {
      if (num[j] < minn) {
        minn = num[j];
        pos = j;
      }
    }
    if (sta.empty() || minn <= sta.top()) {
      for (int j = l; j <= pos; j++) sta.push(num[j]);
      ++pos;
    } else pos = l;
    printf("%d ", sta.top());
    m++;
    sta.pop();
  }
  while (!sta.empty()) {
    printf("%d ", sta.top());
    sta.pop();
  }
  return 0;
}
