#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
const int MAXN = 10200;
char ch[MAXN];
char aaa[MAXN];
struct node {
  char data;
  node *l;
  node *r;
};
node *root;
node nn[MAXN];
stack<node *> a;
queue<node *> aa;
void init() {
  for (int i = 0; i < MAXN; i++) {
    nn[i].data = 0;
    nn[i].l = NULL;
    nn[i].r = NULL;
  }
}
int main() {
  int t;
  while (~scanf("%d", &t)) {
    while (t--) {
      root = NULL;
      cin >> ch;
      init();
      int len = strlen(ch);
      for (int i = 0; i < len; i++) {
        if (isupper(ch[i])) {
          node *q = a.top();
          a.pop();
          node *p = a.top();
          a.pop();
          nn[i].data = ch[i];
          nn[i].l = p;
          nn[i].r = q;
          node *e = &nn[i];
          root = e;
          a.push(e);
        } else {
          nn[i].data = ch[i];
          nn[i].l = NULL;
          nn[i].r = NULL;
          node *y = &nn[i];
          a.push(y);
        }
      }
      node *ff;
      int cnt = 0;
      ff = root;
      aa.push(ff);
      while (!aa.empty()) {
        node *res;
        res = aa.front();
        aa.pop();
        aaa[cnt++] = res->data;
        if (res->l) aa.push(res->l);
        if (res->r) aa.push(res->r);
      }
      for (int i = cnt - 1; i >= 0; i--) cout << aaa[i];
      cout << endl;
    }
  }
  return 0;
}
