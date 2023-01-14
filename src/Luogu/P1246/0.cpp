#include <bits/stdc++.h>
using namespace std;
map<string, int> m;
string now;
void dfs(int len, int step = 0) {
  static int cnt = 0;
  if (step >= len) {
    m[now.c_str()] = ++cnt;
    return;
  }
  for (char i = (step == 0 ? 'a' : now[step - 1] + 1); i <= 'z'; ++i) {
    now[step] = i;
    dfs(len, step + 1);
  }
}
int main() {
  for (int len = 1; len <= 6; ++len) {
    now.clear();
    dfs(len);
  }
  string s;
  cin >> s;
  cout << m[s] << endl;
}
