#include <bits/stdc++.h>
using namespace std;
long long a;
bool flag;
string str;
stack<long long> opnd;
int main() {
  ios::sync_with_stdio(false);
  cin >> str;
  int aa = 0;
  str += '+';
  for (int i = 0; i <= str.length() - 1; i++) {
    if (isdigit(str[i])) aa = aa * 10 + (str[i] - '0');
    if (flag && !isdigit(str[i])) {
      aa = aa % 10000 * opnd.top();
      opnd.pop();
      flag = false;
    }
    if (str[i] == '+') {
      opnd.push(aa % 10000);
      aa = 0;
    }
    if (str[i] == '*') {
      flag = true;
      opnd.push(aa % 10000);
      aa = 0;
    }
  }
  while (!opnd.empty()) {
    a += opnd.top();
    opnd.pop();
  }
  cout << a % 10000 << endl;
  return 0;
}
