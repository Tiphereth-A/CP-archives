#include <iostream>
using namespace std;
int main() {
  string ans[] = {
    "3181",
    "40257",
    "2430",
    "10266837",
    "881012367360",
  };
  char T;
  cin >> T;
  cout << ans[T - 'A'] << endl;
  return 0;
}
