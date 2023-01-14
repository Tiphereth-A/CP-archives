#include <bits/stdc++.h>
int a[3];
char A, B, C;
int main() {
  std::cin >> a[0] >> a[1] >> a[2];
  std::cin >> A >> B >> C;
  std::sort(a, a + 3);
  std::cout << a[A - 'A'] << " " << a[B - 'A'] << " " << a[C - 'A'];
  return 0;
}
