#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
#define REPLU(i, l, r) for (long unsigned int i = (l); i < (r); ++i)
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
const int N = 30;
int n;
vector<int> pile[N];
void findPos(int a, int &p, int &h) {
  REP(i, 0, n)
  REPLU(j, 0, pile[i].size())
  if (pile[i][j] == a) {
    p = i;
    h = j;
    return;
  }
}
void clr(int p, int h) {
  REPLU(i, h + 1, pile[p].size()) {
    int tmp = pile[p][i];
    pile[tmp].push_back(tmp);
  }
  pile[p].resize(h + 1);
}
void pil(int p, int h, int b) {
  REPLU(i, h, pile[p].size())
  pile[b].push_back(pile[p][i]);
  pile[p].resize(h);
}
void print() {
  REP(i, 0, n) {
    cout << i << ":";
    REPLU(j, 0, pile[i].size())
    cout << ' ' << pile[i][j];
    cout << endl;
  }
}
int main() {
  SYNC;
  cin >> n;
  REP(i, 0, n)
  pile[i].push_back(i);
  string s1, s2;
  int a, b;
  while (cin >> s1 >> a >> s2 >> b) {
    int pa, pb, ha, hb;
    findPos(a, pa, ha);
    findPos(b, pb, hb);
    if (pa == pb) continue;
    if (s1 == "move") clr(pa, ha);
    if (s2 == "onto") clr(pb, hb);
    pil(pa, ha, pb);
  }
  print();
  return 0;
}
