#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define SYNC std::ios::sync_with_stdio(false)
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
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
const int N = 50005;
std::string str;
char op;
std::map<std::string, int> m;
std::string diag[N];
int mem_num, fa_id;
int fa[N];
int find(int x) { return x == fa[x] ? x : x = find(fa[x]); }
int main() {
  SYNC;
  _for(i, 1, 50000) fa[i] = i;
  while ((std::cin >> op >> str) && op != '$') {
    if (!m[str]) {
      m[str] = ++mem_num;
      diag[mem_num] = str;
    }
    if (op == '#') fa_id = m[str];
    else if (op == '+') fa[m[str]] = fa_id;
    else if (op == '?')
      std::cout << str << ' ' << diag[find(m[str])] << std::endl;
  }
  return 0;
}
