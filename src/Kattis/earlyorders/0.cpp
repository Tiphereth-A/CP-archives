#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], last[N];
bool in_queue[N];
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) last[a[i]] = i;
  deque<int> ans;
  for (int i = 1; i <= n; ++i)
    if (!in_queue[a[i]]) {
      while (!ans.empty() && a[i] < ans.back() && i < last[ans.back()]) {
        in_queue[ans.back()] = false;
        ans.pop_back();
      }
      in_queue[a[i]] = true;
      ans.push_back(a[i]);
    }
  while (!ans.empty()) {
    cout << ans.front();
    ans.pop_front();
    cout << (ans.empty() ? '\n' : ' ');
  }
  return 0;
}
