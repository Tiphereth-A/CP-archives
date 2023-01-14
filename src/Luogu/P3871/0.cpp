#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <class _T>
class UD_heap {
private:
  priority_queue<_T> dq;
  priority_queue<_T, vector<_T>, greater<_T>> uq;
  bool _init = 0;

public:
  void clear() {
    _init = 0;
    dq = decltype(dq)();
    uq = decltype(uq)();
  }
  void init(_T x) {
    dq.push(x);
    _init = 1;
  }
  void insert(_T x) {
    if (!_init) {
      init(x);
      return;
    }
    (x > dq.top() ? uq.push(x) : dq.push(x));
    if (uq.size() > dq.size() + 1) {
      dq.push(uq.top());
      uq.pop();
    } else if (dq.size() > uq.size() + 1) {
      uq.push(dq.top());
      dq.pop();
    }
  }
  _T get_mid() { return uq.size() > dq.size() ? uq.top() : dq.top(); }
};
UD_heap<int> udq;
char str[10];
int main() {
  int n;
  scanf("%d", &n);
  int _;
  scanf("%d", &_);
  udq.init(_);
  _for(i, 2, n) {
    scanf("%d", &_);
    udq.insert(_);
  }
  int m;
  scanf("%d", &m);
  _for(i, 1, m) {
    scanf(" %s%d", str, &_);
    if (str[0] == 'a') udq.insert(_);
    else printf("%d\n", udq.get_mid());
  }
  return 0;
}
