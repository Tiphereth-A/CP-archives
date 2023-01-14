#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
typedef int __ID_T_Hod;
const int N = 1e5 + 5;
struct node {
  int val;
  __ID_T_Hod pre, suc;
} l[N];
int cnt;
__ID_T_Hod head, id[N];
bool del[N];
int n, m;
void insert(int data, __ID_T_Hod pos, bool p) {
  l[id[data] = ++cnt] = {data, 0, 0};
#define _now l[cnt]
#define _tar l[pos]
#define _pre l[l[pos].pre]
#define _suc l[l[pos].suc]
  if (p) {
    _now.pre = pos;
    _now.suc = _tar.suc;
    if (_tar.suc) _suc.pre = cnt;
    _tar.suc = cnt;
  } else {
    _now.pre = _tar.pre;
    _now.suc = pos;
    if (_tar.pre) _pre.suc = cnt;
    else head = cnt;
    _tar.pre = cnt;
  }
}
int main() {
  cin >> n;
  l[head = id[1] = ++cnt] = {1, 0, 0};
  for (int k, p, i = 2; i <= n; i++) {
    cin >> k >> p;
    insert(i, id[k], p);
  }
  cin >> m;
  for (int x, i = 1; i <= m; ++i) {
    cin >> x;
    del[x] |= 1;
  }
  for (__ID_T_Hod i = head; i; i = l[i].suc) {
    if (!del[l[i].val]) cout << l[i].val << ' ';
  }
  return 0;
}
