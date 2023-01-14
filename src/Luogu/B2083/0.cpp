#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
using namespace std;
void validate_and_init(int &a, int &b, char &c, int &f) {
  string s;
  getline(cin, s);
  const char *ptr = s.data();
  {
    auto [ptr2, ec]{from_chars(ptr, ptr + 3, a)};
    if (ec != std::errc()) exit(__LINE__);
    if (3 > a || a > 100) exit(__LINE__);
    ptr = ptr2;
  }
  if (*ptr++ != ' ') exit(__LINE__);
  {
    auto [ptr2, ec]{from_chars(ptr, ptr + 3, b)};
    if (ec != std::errc()) exit(__LINE__);
    if (5 > b || b > 100) exit(__LINE__);
    ptr = ptr2;
  }
  if (*ptr++ != ' ') exit(__LINE__);
  if (!isgraph(c = *ptr++)) exit(__LINE__);
  if (*ptr++ != ' ') exit(__LINE__);
  {
    auto [ptr2, ec]{from_chars(
      ptr, ptr + min(3, int((ptrdiff_t)s.size() - (ptr - s.data()))), f)};
    if (ec != std::errc()) exit(int(ec));
    if (0 > f || f > 100) exit(__LINE__);
    ptr = ptr2;
    if ((ptr - s.data()) != (ptrdiff_t)s.size()) exit(__LINE__);
  }
}
int main() {
  int a, b, f;
  char c;
  validate_and_init(a, b, c, f);
  int i, j;
  for (i = 1; i <= a; ++i, putchar('\n'))
    for (j = 1; j <= b; ++j)
      putchar((i != 1 && i != a && j != 1 && j != b && !f) ? ' ' : c);
}
