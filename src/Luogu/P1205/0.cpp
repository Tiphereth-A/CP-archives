#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int n;
string s1[N], s2[N];
void rotate() {
  string s3[N];
  for (int i = 0; i < n; ++i) {
    string _;
    for (int j = n - 1; ~j; --j) _.push_back(s1[j][i]);
    s3[i] = _;
  }
  for (int i = 0; i < n; ++i) s1[i] = s3[i];
}
void flip() {
  for (int i = 0; i < n; ++i) reverse(s1[i].begin(), s1[i].end());
}
bool judge() {
  for (int i = 0; i < n; ++i)
    if (s1[i] != s2[i]) return 0;
  return 1;
}
int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> s1[i];
  for (int i = 0; i < n; ++i) cin >> s2[i];
  if (rotate(), judge()) cout << 1;
  else if (rotate(), judge()) cout << 2;
  else if (rotate(), judge()) cout << 3;
  else if (rotate(), flip(), judge()) cout << 4;
  else {
    bool flag = 0;
    flag |= (rotate(), judge());
    flag |= (rotate(), judge());
    flag |= (rotate(), judge());
    cout << (flag ? 5 : 7);
  }
}
