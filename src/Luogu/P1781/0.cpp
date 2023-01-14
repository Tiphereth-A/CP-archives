#include <bits/stdc++.h>
using namespace std;
struct pre {
  int id;
  string num;
} s[21];
bool cmp(pre a, pre b) {
  if (a.num.length() != b.num.length()) return a.num.length() > b.num.length();
  return a.num > b.num;
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i].num;
    s[i].id = i;
  }
  sort(s + 1, s + n + 1, cmp);
  cout << s[1].id << endl << s[1].num;
  return 0;
}
