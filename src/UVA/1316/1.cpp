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
struct a {
  int value;
  bool operator<(const a &other) const { return value > other.value; }
};
std::priority_queue<a> queue;
int main() {
  int n;
  while (cin >> n) {
    memset(p, 0, sizeof(p));
    for (int i = 1; i <= n; ++i) cin >> p[i].price >> p[i].date;
    std::sort(p + 1, p + n + 1);
    unsigned long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      if ((p[i].date == queue.size()) && (queue.top().value < p[i].price)) {
        queue.pop();
        queue.push((a){p[i].price});
      } else if (p[i].date > queue.size()) queue.push((a){p[i].price});
    }
    while (!queue.empty()) {
      ans += queue.top().value;
      queue.pop();
    }
    cout << ans << endl;
  }
  return 0;
}
