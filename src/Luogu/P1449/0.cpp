#include <bits/stdc++.h>
#define gc getchar
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
using namespace std;
char c;
stack<int> s;
int a, b;
int main() {
  while ((c = gc()) != '@') {
    switch (c) {
      case '+': {
        a = s.top();
        s.pop();
        b = s.top();
        s.pop();
        s.push(a + b);
        a = 0;
        break;
      }
      case '-': {
        a = s.top();
        s.pop();
        b = s.top();
        s.pop();
        s.push(b - a);
        a = 0;
        break;
      }
      case '*': {
        a = s.top();
        s.pop();
        b = s.top();
        s.pop();
        s.push(a * b);
        a = 0;
        break;
      }
      case '/': {
        a = s.top();
        s.pop();
        b = s.top();
        s.pop();
        s.push(b / a);
        a = 0;
        break;
      }
      case '.': {
        s.push(a);
        a = 0;
        break;
      }
      default: {
        a = a * 10 + c - '0';
      }
    }
  }
  cout << s.top();
  return 0;
}
