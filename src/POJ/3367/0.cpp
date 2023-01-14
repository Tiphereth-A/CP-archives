#include <cctype>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;
const int N = 5e4 + 5;
struct Tree_node {
  char name;
  int id;
  int lch, rch;
} tree[N];
int cnt_tree;
int main() {
  int kase;
  cin >> kase;
  string line;
  getline(cin, line);
  while (kase--) {
    cnt_tree = 0;
    getline(cin, line);
    stack<int> s;
    for (string::const_iterator it = line.begin(); it != line.end(); ++it) {
      if (islower(*it)) {
        tree[++cnt_tree] = {*it, cnt_tree, 0, 0};
        s.push(cnt_tree);
      } else {
        int rch = s.top();
        s.pop();
        int lch = s.top();
        s.pop();
        tree[++cnt_tree] = {*it, cnt_tree, lch, rch};
        s.push(cnt_tree);
      }
    }
    queue<int> q;
    stack<int> ans;
    q.push(cnt_tree);
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      ans.push(now);
      if (tree[now].lch) q.push(tree[now].lch);
      if (tree[now].rch) q.push(tree[now].rch);
    }
    while (!ans.empty()) {
      cout << tree[ans.top()].name;
      ans.pop();
    }
    cout << endl;
  }
}
