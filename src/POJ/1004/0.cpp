#include <iostream>
using namespace std;
int main() {
  double sum = 0, _;
  for (int i = 1; i <= 12; ++i) {
    cin >> _;
    sum += _;
  }
  cout << '$' << sum / 12;
}
