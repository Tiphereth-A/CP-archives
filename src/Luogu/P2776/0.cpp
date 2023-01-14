#include <bits/stdc++.h>
using namespace std;
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
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
const int N = 1010;
int n, m, t;
map<int, int> team;
queue<int> q, q1[N];
string op;
int main() {
  SYNC;
  cin >> n >> m;
  int a;
  REP(i, 0, n) {
    cin >> a;
    team[i] = a;
  }
  cin >> t;
  while (t--) {
    cin >> op;
    if (op[1] == 'u') {
      int tmp;
      cin >> tmp;
      int tmpt = team[tmp];
      if (q1[tmpt].empty()) q.push(tmpt);
      q1[tmpt].push(tmp);
    } else {
      int tmpt = q.front();
      cout << q1[tmpt].front() << endl;
      q1[tmpt].pop();
      if (q1[tmpt].empty()) q.pop();
    }
  }
  return 0;
}
