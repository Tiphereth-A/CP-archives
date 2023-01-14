#include <iostream>
int main() {
  int a, b, c1, c2, c3;
  std::cin >> a >> b;
  __asm__(
    "movl %1, %%eax\n\t"
    "movl %2, %%ebx\n\t"
    "addl %%ebx, %%eax\n\t"
    "movl %%eax, %0\n\t"
    : "=r"(c1)
    : "r"(a), "r"(b)
    : "%eax");
  __asm__(
    "movl %1, %%eax\n\t"
    "movl %2, %%ebx\n\t"
    "subl %%ebx, %%eax\n\t"
    "movl %%eax, %0\n\t"
    : "=r"(c2)
    : "r"(a), "r"(b)
    : "%eax");
  __asm__(
    "movl %1, %%eax\n\t"
    "movl %2, %%ebx\n\t"
    "imull %%ebx, %%eax\n\t"
    "movl %%eax, %0\n\t"
    : "=r"(c3)
    : "r"(a), "r"(b)
    : "%eax");
  std::cout << c1 << " " << c2 << " " << c3;
  return 0;
}
