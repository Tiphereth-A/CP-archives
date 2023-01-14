#include <bits/stdc++.h>
std::stack<int> s1, s2, ans;
const int prime[] = {2, 3, 5, 7, 11};
int main() {
  int tmp;
  char op;
  bool f = 0;
  while (~scanf("%d", &tmp)) {
    scanf("%c", &op);
    f ? s2.push(tmp) : s1.push(tmp);
    if (op == '+') f = 1;
  }
  int cnt = 0, a = 0;
  while (!s1.empty() && !s2.empty()) {
    a += s1.top() + s2.top();
    s1.pop();
    s2.pop();
    ans.push(a % prime[cnt]);
    a /= prime[cnt++];
  }
  while (!s1.empty()) {
    a += s1.top();
    s1.pop();
    ans.push(a % prime[cnt]);
    a /= prime[cnt++];
  }
  while (!s2.empty()) {
    a += s2.top();
    s2.pop();
    ans.push(a % prime[cnt]);
    a /= prime[cnt++];
  }
  if (a) ans.push(a);
  while (cnt--) {
    printf("%d,", ans.top());
    ans.pop();
  }
  printf("%d", ans.top());
  return 0;
}
