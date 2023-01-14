#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using u64 = uint64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
char getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <class T>
void read(T &x) {
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) ch = getc();
  while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
const int OFFSET = 1;
const int N = 1e7 + OFFSET;
namespace radix_sort {
using data_type = unsigned;
using size_type = unsigned;
using pointer = data_type *;
using bucket = size_type[256];
bucket cnt0, cnt8, cnt16, cnt24;
void main(pointer a, pointer b, size_type n) {
  for (pointer _ = a + n, i = a; i < _; ++i) {
    ++cnt0[*i & 255];
    ++cnt8[*i >> 8 & 255];
    ++cnt16[*i >> 16 & 255];
    ++cnt24[*i >> 24 & 255];
  }
  for (size_type i = 1; i < 256; ++i) {
    cnt0[i] += cnt0[i - 1];
    cnt8[i] += cnt8[i - 1];
    cnt16[i] += cnt16[i - 1];
    cnt24[i] += cnt24[i - 1];
  }
  for (pointer i = a + n; --i >= a;) b[--cnt0[*i & 255]] = *i;
  for (pointer i = b + n; --i >= b;) a[--cnt8[*i >> 8 & 255]] = *i;
  for (pointer i = a + n; --i >= a;) b[--cnt16[*i >> 16 & 255]] = *i;
  for (pointer i = b + n; --i >= b;) a[--cnt24[*i >> 24 & 255]] = *i;
}
}  // namespace radix_sort
u32 a[N];
u64 b[N];
u32 a_head, b_head, b_tail;
int main() {
  u32 n;
  read(n);
  _for(i, 0, n - 1) read(a[i]);
  u64 ans = 0;
  radix_sort::main(a, (u32 *)b, n);
  u64 x, y;
  _for(i, 1u, n - 1) {
    x = ((b_head == b_tail) || (a_head < n && a[a_head] < b[b_head])) ?
          a[a_head++] :
          b[b_head++];
    y = ((b_head == b_tail) || (a_head < n && a[a_head] < b[b_head])) ?
          a[a_head++] :
          b[b_head++];
    b[b_tail++] = x + y;
    ans += x + y;
  }
  cout << ans;
  return 0;
}
