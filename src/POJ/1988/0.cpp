#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int fa[N], sum[N], num[N];
int find(int x) {
  if (x == fa[x]) return x;
  int fx = find(fa[x]);
  sum[x] += sum[fa[x]];
  return fa[x] = fx;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t, x, y, fx, fy;
  cin >> t;
  for (int i = 1; i < N; ++i) fa[i] = i;
  for (int i = 1; i < N; ++i) num[i] = 1;
  char op;
  while (t--) {
    cin >> op >> x;
    fx = find(x);
    if (op == 'M') {
      cin >> y;
      fy = find(y);
      sum[fx] += num[fy];
      num[fy] += num[fx];
      num[fx] = 0;
      fa[fx] = fy;
    } else cout << sum[x] << '\n';
  }
  return 0;
}
