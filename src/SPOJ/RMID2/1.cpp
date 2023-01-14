#include <cstdio>
#include <queue>
using namespace std;
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    priority_queue<int, vector<int>, greater<int>> uq;
    priority_queue<int> dq;
    int _;
    scanf("%d", &_);
    dq.push(_);
    while (1) {
      scanf("%d", &_);
      if (_ > 0) {
        (_ > dq.top() ? uq.push(_) : dq.push(_));
        if (uq.size() > dq.size() + 1) {
          dq.push(uq.top());
          uq.pop();
        } else if (dq.size() > uq.size() + 1) {
          uq.push(dq.top());
          dq.pop();
        }
      } else if (_ == -1) {
        if (uq.size() > dq.size()) {
          printf("%d\n", uq.top());
          uq.pop();
        } else {
          printf("%d\n", dq.top());
          dq.pop();
        }
      } else break;
    }
  __end_kase:;
  }
  return 0;
}
