#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
struct node {
  string name;
  int solve, sans[15], grade;
  bool operator<(const node &rhs) const {
    return grade == rhs.grade ? name < rhs.name : grade > rhs.grade;
  }
} s[1005];
int pgrade[15] = {0};
int main() {
  int sn, pn, g;
  while (cin >> sn && sn && cin >> pn >> g) {
    for (int i = 0; i < pn; ++i) cin >> pgrade[i];
    for (int i = 0; i < sn; ++i) {
      s[i].grade = 0;
      cin >> s[i].name >> s[i].solve;
      for (int j = 0; j < s[i].solve; ++j) {
        scanf("%d", &s[i].sans[j]);
        s[i].grade += pgrade[s[i].sans[j] - 1];
      }
    }
    sort(s, s + sn);
    int ans = sn;
    for (int i = 0; i < sn; ++i)
      if (s[i].grade < g) {
        ans = i;
        break;
      }
    cout << ans << endl;
    for (int i = 0; i < ans; ++i)
      cout << s[i].name << ' ' << s[i].grade << endl;
  }
  return 0;
}
