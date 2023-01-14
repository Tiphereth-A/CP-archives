#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
const int N = 1e4 + 5;
struct node {
  int price, date;
  bool operator<(const node &other) const { return date < other.date; }
} p[N];
int main() {
  int n;
  while (cin >> n) {
    memset(p, 0, sizeof(p));
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
    for (int i = 1; i <= n; ++i) cin >> p[i].price >> p[i].date;
    std::sort(p + 1, p + n + 1);
    unsigned long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      if ((p[i].date == queue.size()) && (queue.top() < p[i].price)) {
        queue.pop();
        queue.push(p[i].price);
      } else if (p[i].date > queue.size()) queue.push(p[i].price);
    }
    while (!queue.empty()) {
      ans += queue.top();
      queue.pop();
    }
    cout << ans << endl;
  }
  return 0;
}
