#include <cstdio>
#include <cstring>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
class SegTree {
private:
  struct Node {
    u64 val, lazy;
    Node(u64 _val = 0, u64 _lazy = 0): val(_val), lazy(_lazy) {}
  } t[N * 4];
  void _push_up(std::size_t index) {
    t[index].val = t[index << 1].val | t[index << 1 | 1].val;
  }
  void _push_down(std::size_t index) {
    if (!t[index].lazy) return;
    t[index << 1] = Node(t[index].lazy, t[index].lazy);
    t[index << 1 | 1] = Node(t[index].lazy, t[index].lazy);
    t[index].lazy = 0;
  }
  void _update(std::size_t L,
               std::size_t R,
               u64 k,
               std::size_t index = 1,
               std::size_t l = 1,
               std::size_t r = N - 1) {
    if (L <= l && r <= R) {
      t[index] = Node(k, k);
      return;
    }
    std::size_t mid = l + ((r - l) >> 1);
    _push_down(index);
    if (mid >= L) _update(L, R, k, index << 1, l, mid);
    if (mid < R) _update(L, R, k, index << 1 | 1, mid + 1, r);
    _push_up(index);
  }
  u64 _query(std::size_t L,
             std::size_t R,
             std::size_t index = 1,
             std::size_t l = 1,
             std::size_t r = N - 1) {
    if (L <= l && r <= R) return t[index].val;
    std::size_t mid = l + ((r - l) >> 1);
    u64 ans = 0;
    _push_down(index);
    if (mid >= L) ans |= _query(L, R, index << 1, l, mid);
    if (mid < R) ans |= _query(L, R, index << 1 | 1, mid + 1, r);
    return ans;
  }

public:
  SegTree() {}
  void clear() { memset(t, 0, sizeof(t)); }
  void update(std::size_t l, std::size_t r, u64 val) { _update(l, r, val); }
  u64 query(std::size_t l, std::size_t r) { return _query(l, r); }
};
SegTree t1;
unsigned long long popcount(unsigned long long u) {
  u = (u & 0x5555555555555555ll) + ((u >> 1) & 0x5555555555555555ll);
  u = (u & 0x3333333333333333ll) + ((u >> 2) & 0x3333333333333333ll);
  u = (u & 0x0F0F0F0F0F0F0F0Fll) + ((u >> 4) & 0x0F0F0F0F0F0F0F0Fll);
  u = (u & 0x00FF00FF00FF00FFll) + ((u >> 8) & 0x00FF00FF00FF00FFll);
  u = (u & 0x0000FFFF0000FFFFll) + ((u >> 16) & 0x0000FFFF0000FFFFll);
  u = (u & 0x00000000FFFFFFFFll) + ((u >> 32) & 0x00000000FFFFFFFFll);
  return u;
}
int main() {
  int l, t, o;
  scanf("%d %d %d\n", &l, &t, &o);
  t1.update(1, l, 2);
  char op;
  int a, b, c;
  _for(i, 1, o) {
    if ((op = getchar()) == 'C') {
      scanf("%d %d %d\n", &a, &b, &c);
      if (a > b) a ^= b ^= a ^= b;
      t1.update(a, b, 1 << c);
    } else {
      scanf("%d %d\n", &a, &b);
      if (a > b) a ^= b ^= a ^= b;
      printf("%d\n", popcount(t1.query(a, b)));
    }
  }
  t1.clear();
  return 0;
}
