#include <bits/stdc++.h>
using namespace std;
int main() {
  stack<int> num;
  while (1) {
    int n;
    cin >> n;
    if (!n) break;
    num.push(n);
  };
  while (!num.empty()) {
    cout << num.top() << " ";
    num.pop();
  }
  return 0;
}
