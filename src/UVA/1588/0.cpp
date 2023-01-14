#include <iostream>
#include <string>
using namespace std;
int main() {
  string a, b;
  while (cin >> a >> b) {
    int len_a = a.size(), len_b = b.size();
    a += string(10005, '\0');
    b += string(10005, '\0');
    int ans_1 = 0, ans_2 = 0;
    for (int i = 1; i <= len_b + 1; ++i) {
      bool f = true;
      for (int j = 0; j < len_a; ++j)
        if (b[i + j - 1] + a[j] > 99) {
          f = false;
          break;
        }
      if (f) {
        ans_1 = max(len_b, len_a + i - 1);
        break;
      }
    }
    for (int i = 1; i <= len_a + 1; ++i) {
      bool f = true;
      for (int j = 0; j < len_b; ++j)
        if (a[i + j - 1] + b[j] > 99) {
          f = false;
          break;
        }
      if (f) {
        ans_2 = max(len_a, len_b + i - 1);
        break;
      }
    }
    cout << min(ans_1, ans_2) << endl;
  }
}
