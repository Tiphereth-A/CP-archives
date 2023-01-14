#include <bits/stdc++.h>
using namespace std;
int cnt, n;
void search(int num) {
  if (num > n) return;
  else cnt++;
  search(num * 10);
  search(num * 10 + 1);
}
int main() {
  cin >> n;
  search(1);
  cout << cnt;
  return 0;
}
