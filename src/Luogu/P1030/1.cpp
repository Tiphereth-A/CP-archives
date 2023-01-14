#include <bits/stdc++.h>
#include <bits/stdc++.h>*/
#include <bits/stdc++.h>
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
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
void read(A &a, B &b, C &c, D &d) {
  read(a), read(b), read(c), read(d);
}
using namespace std;
string in, af;
void pre(string in, string af) {
  if (in.size() > 0) {
    char c = af[af.size() - 1];
    cout << c;
    int r = in.find(c);
    pre(in.substr(0, r), af.substr(0, r));
    pre(in.substr(r + 1), af.substr(r, in.size() - r - 1));
  }
}
int main() {
  cin >> in >> af;
  pre(in, af);
  return 0;
}
