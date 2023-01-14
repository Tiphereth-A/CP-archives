#include <bits/stdc++.h>
using namespace std;
const char nums[] = "0123456789ABCDEF";
int main() {
  int n, m;
  string str;
  cin >> n >> str >> m;
  long long num = 0;
  for (char ch : str) (num *= n) += isalpha(ch) ? ch - 'A' + 10 : ch - '0';
  str.clear();
  while (num) {
    str.push_back(nums[num % m]);
    num /= m;
  }
  for (auto rit = str.rbegin(); rit != str.rend(); ++rit) cout << *rit;
  return 0;
}
