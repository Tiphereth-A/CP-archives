#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
priority_queue<int> dq;
priority_queue<int, vector<int>, greater<int>> uq;
int main() {
  int n;
  scanf("%d", &n);
  int _;
  scanf("%d", &_);
  dq.push(_);
  printf("%d\n", _);
  _for(i, 2, n) {
    scanf("%d", &_);
    (_ > dq.top() ? uq.push(_) : dq.push(_));
    if (uq.size() > dq.size() + 1) {
      dq.push(uq.top());
      uq.pop();
    } else if (dq.size() > uq.size() + 1) {
      uq.push(dq.top());
      dq.pop();
    }
    if (i % 2) printf("%d\n", (uq.size() > dq.size() ? uq.top() : dq.top()));
  }
  return 0;
}
