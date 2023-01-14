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
template <class Tp>
class UDHeap {
private:
  std::priority_queue<Tp> dq;
  std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>> uq;

public:
  UDHeap() {}
  UDHeap<Tp> &clear() {
    while (!dq.empty()) dq.pop();
    while (!uq.empty()) uq.pop();
    return *this;
  }
  UDHeap<Tp> &insert(const Tp &x) {
    if (dq.empty() && uq.empty()) {
      dq.push(x);
      return *this;
    }
    (x > dq.top() ? uq.push(x) : dq.push(x));
    if (uq.size() > dq.size() + 1) {
      dq.push(uq.top());
      uq.pop();
    } else if (dq.size() > uq.size() + 1) {
      uq.push(dq.top());
      dq.pop();
    }
    return *this;
  }
  Tp get_mid() const { return uq.size() > dq.size() ? uq.top() : dq.top(); }
  UDHeap<Tp> &pop_mid() {
    uq.size() > dq.size() ? uq.pop() : dq.pop();
    return *this;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  while (!cin.eof()) {
    int n;
    UDHeap<int> udh;
    udh.clear();
    while ((cin >> n), n)
      if (~n) udh.insert(n);
      else {
        cout << udh.get_mid() << '\n';
        udh.pop_mid();
      }
    cout << '\n';
  }
  return 0;
}
