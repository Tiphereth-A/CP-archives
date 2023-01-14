#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
using LL = long long;
using PII = pair<LL, LL>;
int T;
vector<PII> nums;
LL n, m;
bool f(LL u) {
  LL cnt = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i].first <= u) cnt += (u / nums[i].first) * nums[i].second;
  }
  if (cnt >= n) return 1;
  return 0;
}
void solve() {
  nums.clear();
  cin >> n >> m;
  LL a[m + 10], c[m + 10];
  LL sum = 0;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
    sum += a[i];
  }
  map<LL, LL> st;
  for (int i = 0; i < m; i++) {
    cin >> c[i];
    st[c[i]] += a[i];
  }
  for (auto i : st) nums.push_back(i);
  sort(nums.begin(), nums.end());
  n -= sum;
  if (n <= 0) {
    cout << 1 << endl;
    return;
  }
  LL l = 1, r = 1e12;
  while (l < r) {
    LL mid = l + r >> 1;
    if (f(mid) == 1) r = mid;
    else l = mid + 1;
  }
  cout << r + 1;
  cout << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> T;
  while (T--) { solve(); }
}
