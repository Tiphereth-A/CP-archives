#include <bits/stdc++.h>
using namespace std;
int main() {
  int a[3];
  cin >> a[0] >> a[1] >> a[2];
  sort(a, a + 3);
  if (a[0] + a[1] <= a[2]) {
    cout << "Not triangle";
    return 0;
  }
  if (a[0] * a[0] + a[1] * a[1] == a[2] * a[2]) cout << "Right triangle";
  else if (a[0] * a[0] + a[1] * a[1] > a[2] * a[2]) cout << "Acute triangle";
  else if (a[0] * a[0] + a[1] * a[1] < a[2] * a[2]) cout << "Obtuse triangle";
  cout << endl;
  if (a[0] == a[1] || a[1] == a[2] || a[0] == a[2])
    cout << "Isosceles triangle" << endl;
  if (a[0] == a[1] && a[1] == a[2]) cout << "Equilateral triangle";
}
