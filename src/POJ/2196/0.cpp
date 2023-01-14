#include <iostream>
using namespace std;
int calc(int k, int b) {
  int sum = 0;
  while (k) {
    sum += k % b;
    k = k / b;
  }
  return sum;
}
int main() {
  for (int i = 2991; i < 10000; ++i) {
    int s = i % 10 + (i / 10) % 10 + (i / 100) % 10 + (i / 1000);
    if (s == calc(i, 12) && s == calc(i, 16)) cout << i << endl;
  }
  return 0;
}
