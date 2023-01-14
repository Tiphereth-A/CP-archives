#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n;
  string s;
  cin >> n >> s;
  long long ans = 0;
  for (char ch : s) ((ans *= 10) += ch - '0') %= n;
  cout << (ans ? ans : n) << endl;
}
