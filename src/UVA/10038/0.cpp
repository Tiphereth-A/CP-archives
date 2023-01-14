#include <algorithm>
#include <iostream>
using namespace std;
int cnt, coord[100005], jump[100005];
bool flag = 1;
int main() {
  ios::sync_with_stdio(false);
  while (cin >> cnt) {
    for (int i = 0; i < cnt; i++) cin >> coord[i];
    for (int i = 0; i < cnt - 1; i++) jump[i] = abs(coord[i] - coord[i + 1]);
    sort(jump, jump + cnt - 1);
    for (int i = 0; i < cnt - 1; i++)
      if (jump[i] - jump[i - 1] != 1) {
        flag = 0;
        break;
      }
    cout << (flag ? "J" : "Not j") << "olly" << endl;
    flag = 1;
  }
}
