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
char c;
std::string str;
int main() {
  while ((c = getchar()) != EOF) {
    if (c == '1') str += "hongliyu";
    else if (c == '2') str += "lvliyu";
    else if (c == '3') str += "lv";
  }
  std::cout << str;
  return 0;
}
