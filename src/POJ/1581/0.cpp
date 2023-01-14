#include <iostream>
#include <string>
using namespace std;
struct Node {
  string name;
  int num, score;
  bool operator<(const Node &rhs) const {
    return num == rhs.num ? score < rhs.score : num > rhs.num;
  }
} _[205];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int score = 0, num = 0;
    string name;
    cin >> name;
    for (int j = 0; j < 4; ++j) {
      int a, b;
      cin >> a >> b;
      if (b > 0) {
        ++num;
        score += (b + (a - 1) * 20);
      }
    }
    _[i].name = name;
    _[i].num = num;
    _[i].score = score;
  }
  Node *ans = _;
  for (int i = 1; i < n; ++i)
    if (!(*ans < _[i])) ans = &_[i];
  cout << ans->name << " " << ans->num << " " << ans->score << endl;
  return 0;
}
