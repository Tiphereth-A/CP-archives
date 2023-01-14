#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  i64 n;
  cin >> n;
  if (n % 10) {
    cout << "1\n" << n % 10;
    return 0;
  }
  cout << "2\n";
  return 0;
}
