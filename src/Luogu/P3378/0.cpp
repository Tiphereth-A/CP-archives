#include <bits/stdc++.h>
using namespace std;
#define gi(a)                                            \
  do {                                                   \
    char ch;                                             \
    while ((a = getchar()) > '9' || a < '0');            \
    for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; \
         a = a * 10 + ch - '0');                         \
  } while (0)
priority_queue<int, vector<int>, greater<int>> q;
int n, a, b;
int main() {
  gi(n);
  for (int i = 1; i <= n; i++) {
    gi(a);
    switch (a) {
      case 1:
        gi(b);
        q.push(b);
        break;
      case 2: printf("%d\n", q.top()); break;
      case 3: q.pop();
    }
  }
  return 0;
}
