#include <iostream>
#include <queue>
#include <set>
#include <vector>
const int dx[3] = {2, 3, 5};
std::priority_queue<i64, std::vector<i64>, std::greater<i64>> q;
std::set<i64> s;
int main() {
  q.push(1);
  s.insert(1);
  for (int i = 1; i < 1500; ++i) {
    i64 tmp = q.top();
    q.pop();
    for (int j = 0; j < 3; ++j) {
      i64 tmpp = tmp * dx[j];
      if (!s.count(tmpp)) {
        s.insert(tmpp);
        q.push(tmpp);
      }
    }
  }
  std::cout << "The 1500'th ugly number is " << q.top() << "." << std::endl;
  return 0;
}
