#include <iostream>
#include <string>
using namespace std;
const int N = 26 + 1;
i64 c[N][N] = {{1}, {1, 1}};
int main() {
  for (int i = 2; i < N; ++i) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; ++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }
  string str;
  cin >> str;
  for (string::const_iterator it = str.begin() + 1; it != str.end(); ++it)
    if (*it <= *(it - 1)) {
      cout << 0 << endl;
      return 0;
    }
  if (str.size() == 1) {
    cout << str[0] - 'a' + 1;
    return 0;
  }
  unsigned long long ans = 0;
  for (int i = 1; i < str.size(); ++i) ans += c[26][i];
  for (int j = 'a'; j < str[0]; ++j) ans += c['z' - j][str.size() - 1];
  for (int i = 1; i < str.size(); ++i)
    for (int j = str[i - 1] + 1; j < str[i]; ++j)
      ans += c['z' - j][str.size() - i - 1];
  cout << ans + 1;
}
