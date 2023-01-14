#include <bits/stdc++.h>
int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    (x *= 10) += c - '0';
    c = getchar();
  }
  return x * f;
}
int main() {
  puts("Happy Birthday LZU!");
  return 0;
}
