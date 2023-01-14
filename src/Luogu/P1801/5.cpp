#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int Add[MAXN], Get[MAXN];
int M, N, k;
struct Node {
  Node *ch[2];
  int priority;
  int v, size, cnt;
  int cmp(const int &x) const {
    if (x == v) return -1;
    return x < v ? 0 : 1;
  }
  Node(): priority(1 << 30), v(0), size(0), cnt(0) { ch[0] = ch[1] = this; }
  Node(int v);
};
Node *Null(new Node);
Node *Root = Null;
Node ::Node(const int v): priority(rand()), v(v), size(1), cnt(1) {
  ch[0] = ch[1] = Null;
}
int read() {
  int s = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
  return s * f;
}
void maintain(Node *&o) { o->size = o->ch[0]->size + o->ch[1]->size + o->cnt; }
void rotate(Node *&o, const int &d) {
  Node *k = o->ch[d ^ 1];
  o->ch[d ^ 1] = k->ch[d];
  k->ch[d] = o;
  maintain(o);
  maintain(k);
  o = k;
}
void Insert(Node *&o, const int &x) {
  if (o == Null) o = new Node(x);
  else {
    int d = o->cmp(x);
    if (d == -1) {
      ++o->cnt;
      maintain(o);
      return;
    }
    Insert(o->ch[d], x);
    if (o->ch[d]->priority > o->priority) rotate(o, d ^ 1);
  }
  maintain(o);
}
int kth(Node *&o, const int &K) {
  if (o == Null || K <= 0 || K > o->size) return 0;
  int s = (o->ch[0] == Null ? 0 : o->ch[0]->size);
  if (K >= s + 1 && K <= s + o->cnt) return o->v;
  else if (K <= s) return kth(o->ch[0], K);
  return kth(o->ch[1], K - s - o->cnt);
}
int main() {
  int i, j;
  M = read(), N = read();
  for (i = 1; i <= M; i++) Add[i] = read();
  for (i = 1; i <= N; i++) Get[i] = read();
  sort(Get + 1, Get + N + 1);
  for (i = 1, j = 1; i <= M; i++) {
    Insert(Root, Add[i]);
    while (Get[j] == i) {
      printf("%d\n", kth(Root, ++k));
      j++;
    }
  }
  return 0;
}
