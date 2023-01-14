#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1010;
int main() {
  ios::sync_with_stdio(false);
  int n, cnt;
  while (cin >> n && n) {
    int a, b;
    map<int, int> team;
    cout << "Scenario #" << ++cnt << endl;
    _for(i, 1, n) {
      cin >> a;
      while (a--) {
        cin >> b;
        team[b] = i;
      }
    }
    queue<int> q, q1[N];
    string op;
    while (cin >> op && op[0] != 'S') {
      if (op[0] == 'E') {
        int tmp;
        cin >> tmp;
        int tmpt = team[tmp];
        if (q1[tmpt].empty()) q.push(tmpt);
        q1[tmpt].push(tmp);
      } else {
        int tmpt = q.front();
        cout << q1[tmpt].front() << endl;
        q1[tmpt].pop();
        if (q1[tmpt].empty()) q.pop();
      }
    }
    cout << endl;
  }
  return 0;
}
