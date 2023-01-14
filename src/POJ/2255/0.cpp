#include <cstdio>
#include <cstring>
const int N = 35;
char pre[N], in[N];
void solve(int l_in, int r_in, int l_pre, int r_pre) {
  if (l_in > r_in) return;
  int pos;
  char root = pre[l_pre];
  for (pos = l_in; pos <= r_in; ++pos)
    if (in[pos] == root) break;
  int len = pos - l_in;
  solve(l_in, pos - 1, l_pre + 1, l_pre + len);
  solve(pos + 1, r_in, l_pre + len + 1, r_pre);
  putchar(root);
}
int main() {
  while (~scanf("%s %s\n", pre + 1, in + 1)) {
    int n = strlen(pre + 1);
    solve(1, n, 1, n);
    putchar('\n');
  }
}
