#include <bits/stdc++.h>
const int N = 1e5 + 5;
namespace fastIO {
#define gc()                                                    \
  (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), \
               (iS == iT ? EOF : *iS++)) :                      \
              *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], obuff[SIZ], *oS = obuff, *oT = oS + SIZ - 1, fu[110],
                                       c;
int fr;
void out() {
  fwrite(obuff, 1, oS - obuff, stdout);
  oS = obuff;
}
template <class Type>
void read(Type &x) {
  Type y = 1;
  for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc());
  c == '-' ? y = -1 : x = (c & 15);
  for (c = gc(); c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  x *= y;
}
template <class Type>
void print(Type x, char text = '\n') {
  if (x < 0) *oS++ = '-', x *= -1;
  if (x == 0) *oS++ = '0';
  while (x) fu[++fr] = x % 10 + '0', x /= 10;
  while (fr) *oS++ = fu[fr--];
  *oS++ = text;
  out();
}
}  // namespace fastIO
using namespace fastIO;
std::priority_queue<int> q;
int a[N], b[N], ans[N];
int n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) read(a[i]);
  for (int i = 1; i <= n; ++i) read(b[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int tmp = a[i] + b[j];
      if (q.size() < n) q.push(tmp);
      else {
        if (q.top() > tmp) {
          q.pop();
          q.push(tmp);
        } else break;
      }
    }
  for (int i = n; i; --i) {
    ans[i] = q.top();
    q.pop();
  }
  for (int i = 1; i <= n; ++i) print(ans[i], ' ');
  return 0;
}
