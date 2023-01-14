#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct node {
  int val;
  int pre, suc;
} lists[N];
int cnt, head, id[N];
bool deleted[N];
void insert(int data, int pos, bool f) {
  lists[id[data] = ++cnt] = {data, 0, 0};
  if (f) {
    lists[cnt].pre = pos;
    lists[cnt].suc = lists[pos].suc;
    if (lists[pos].suc) lists[lists[pos].suc].pre = cnt;
    lists[pos].suc = cnt;
  } else {
    lists[cnt].pre = lists[pos].pre;
    lists[cnt].suc = pos;
    (lists[pos].pre ? lists[lists[pos].pre].suc : head) = cnt;
    lists[pos].pre = cnt;
  }
}
int main() {
  int n, m;
  cin >> n;
  lists[head = id[1] = ++cnt] = {1, 0, 0};
  for (int i = 2, k, p; i <= n; ++i) {
    cin >> k >> p;
    insert(i, id[k], p);
  }
  cin >> m;
  for (int i = 1, x; i <= m; ++i) {
    cin >> x;
    deleted[x] |= 1;
  }
  for (int i = head; i; i = lists[i].suc)
    if (!deleted[lists[i].val]) cout << lists[i].val << ' ';
}
