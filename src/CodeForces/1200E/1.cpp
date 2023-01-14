#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10, b = 63;
const int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
long long b1[N], b2[N];
long long h11, h12, h21, h22;
int func(char ch) {
  assert(isalnum(ch));
  if (isupper(ch)) return ch - 'A' + 1;
  if (islower(ch)) return ch - 'a' + 1 + 26;
  if (isdigit(ch)) return ch - '0' + 1 + 52;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  b1[1] = b2[1] = 1;
  int n;
  cin >> n;
  string str1, str2;
  cin >> str1;
  int len1 = str1.size();
  bool f = false;
  for (int i = 2; i <= n; i++) {
    cin >> str2;
    int len2 = str2.size();
    int len = min(len1, len2);
    h11 = h12 = h21 = h22 = 0;
    b1[1] = b2[1] = 1;
    int pos = 0;
    for (int l = 1; l <= len; l++) {
      h11 = ((h11 * b % mod1) + func(str1[len1 - l])) % mod1;
      h12 = (h12 + b1[l] * func(str2[l - 1]) % mod1) % mod1;
      b1[l + 1] = b1[l] * b % mod1;
      h21 = ((h21 * b % mod2) + func(str1[len1 - l])) % mod2;
      h22 = (h22 + b2[l] * func(str2[l - 1]) % mod2) % mod2;
      b2[l + 1] = b2[l] * b % mod2;
      if (h11 == h12 && h21 == h22) pos = l;
    }
    for (int l = len1 - pos, k = 0; k <= len2 - 1; l++, k++) {
      len1 = max(len1, l + 1);
      str1.resize(len1);
      str1[l] = str2[k];
    }
  }
  for (int i = 0; i <= len1 - 1; i++) cout << str1[i];
  return 0;
}
