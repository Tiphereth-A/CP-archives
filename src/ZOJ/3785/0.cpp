#include <iostream>
using namespace std;
const char weeks[][10] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int table[43] = {0, 1, 4, 6, 4, 3, 1, 0, 1, 1, 4, 2, 1, 6, 0,
                       1, 2, 5, 1, 5, 1, 0, 1, 4, 1, 4, 4, 6, 0, 1,
                       1, 3, 2, 6, 1, 0, 1, 2, 2, 1, 2, 6, 0};
const int sum_of_table = 6;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    long long n;
    cin >> n;
    long long ans = (n / 42 * sum_of_table) + 6;
    for (int i = 1; i <= n % 42; ++i) ans += table[i];
    cout << weeks[ans % 7] << endl;
  }
}
