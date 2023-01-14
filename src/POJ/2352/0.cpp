#include <cstdio>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 5e4 + OFFSET;
class BIT {
private:
  int tree[N];
  int lowbit(int x) { return x & (-x); }

public:
  void add(int pos) {
    for (int i = pos; i < N; i += lowbit(i)) ++tree[i];
  }
  int query(int pos) {
    int ret = 0;
    for (int i = pos; i; i -= lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT tr;
int level[N];
int main() {
  int n;
  scanf("%d", &n);
  int x, y;
  _for(i, 1, n) {
    scanf("%d%d", &x, &y);
    ++level[tr.query(++x)];
    tr.add(x);
  }
  _for(i, 0, n - 1) printf("%d\n", level[i]);
  return 0;
}
