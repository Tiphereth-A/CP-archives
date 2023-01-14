#include <bits/stdc++.h>
using namespace std;
const int N = 500;
int cnt1[N], cnt2[N];
int main() {
  string s1, s2;
  cin >> s1 >> s2;
  for (char ch : s1) ++cnt1[ch];
  for (char ch : s2) ++cnt2[ch];
  for (int i = 'a'; i <= 'z'; ++i)
    if (cnt1[i] && cnt2[i]) {
      cout << "yes";
      return 0;
    }
  cout << "no";
  return 0;
}
