#include <bits/stdc++.h>
using std::cin;
using std::cout;
int a, b;
std::pair<long long, long long> exgcd(int a, int b) {
  if (b == 0) return std::make_pair<long long, long long>(1, 0);
  std::pair<long long, long long> tmp = exgcd(b, a % b);
  return std::make_pair(tmp.second, tmp.first - a / b * tmp.second);
}
int main() {
  cin >> a >> b;
  cout << (exgcd(a, b).first + b) % b;
  return 0;
}
