#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  cout << (min(n, m) != int(std::numbers::phi * abs(n - m))) << '\n';
}
