#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;
  int _;
  for (int i = 1; i <= n; ++i) {
    cin >> _;
    pq.push(_);
  }
  cout << pq.top();
}
