#include <bits/stdc++.h>
const int MAXN = 200000 + 10;
int a[MAXN], g[MAXN];
struct node {
  node *left, *right;
  int w, n;
  node(int t) {
    left = right = NULL;
    w = 1;
    n = t;
  }
} *h;
void insert(node *p, int x) {
  p->w++;
  if (x < p->n) {
    if (p->left) insert(p->left, x);
    else {
      node *q = new node(x);
      p->left = q;
    }
  } else {
    if (p->right) insert(p->right, x);
    else {
      node *q = new node(x);
      p->right = q;
    }
  }
}
void find(node *p, int v) {
  if (p->left && p->right) {
    if (p->left->w >= v) find(p->left, v);
    else if (p->left->w + 1 == v) printf("%d\n", p->n);
    else find(p->right, v - p->left->w - 1);
  } else if (p->left) {
    if (v == p->left->w + 1) printf("%d\n", p->n);
    else find(p->left, v);
  } else if (v == 1) printf("%d\n", p->n);
  else find(p->right, v - 1);
}
int main() {
  int m, n, t = 1;
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &g[i]);
  h = new node(a[1]);
  if (g[t] == 1) {
    printf("%d\n", a[1]);
    t++;
  }
  for (int i = 2; i <= m; i++) {
    insert(h, a[i]);
    while (t <= n && g[t] == i) {
      find(h, t);
      t++;
    }
  }
  return 0;
}
