#include <bits/stdc++.h>
using namespace std;
int main() {
  int pen, num, n, p;
  long prize, min = 10000000;
  cin >> pen;
  for (int i = 1; i <= 3; i++) {
    cin >> n >> p;
    num = pen / n;
    if (pen % n) num++;
    prize = num * p;
    if (prize < min) min = prize;
  };
  cout << min;
  return 0;
}
