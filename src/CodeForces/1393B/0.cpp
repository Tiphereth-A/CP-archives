#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int cnt[N];
int cnt_2, cnt_4, cnt_6, cnt_8;
void modify(int num, char op = '+') {
#define _plus(a) \
  if (cnt[num] == a) ++cnt_##a
#define _minus(a) \
  if (cnt[num] == a - 1) --cnt_##a
  if (op == '+') {
    ++cnt[num];
    _plus(8);
    _plus(6);
    _plus(4);
    _plus(2);
  } else if (op == '-') {
    --cnt[num];
    _minus(8);
    _minus(6);
    _minus(4);
    _minus(2);
  }
#undef _plus
#undef _minus
}
bool judge() {
  if (cnt_8) return true;
  if (cnt_6)
    if (cnt_6 >= 2 || cnt_4 >= 2 || cnt_2 >= 2) return true;
  if (cnt_4)
    if (cnt_4 >= 2 || cnt_2 >= 3) return true;
  return false;
}
int main() {
  int n;
  cin >> n;
  for (int i = 1, _; i <= n; ++i) {
    cin >> _;
    modify(_);
  }
  int q;
  cin >> q;
  char op;
  for (int i = 1, _; i <= q; ++i) {
    cin >> op >> _;
    modify(_, op);
    if (judge()) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
  return 0;
}
