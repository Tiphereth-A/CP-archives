#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 3e3 + 5;
int post[N], in[N];
void solve(int l_in, int r_in, int l_post, int r_post) {
  if (l_in > r_in) return;
  int pos = std::lower_bound(in + l_in, in + r_in, post[r_post]) - in;
  solve(pos + 1, r_in, l_post + pos - l_in, r_post - 1);
  solve(l_in, pos - 1, l_post, l_post + pos - l_in - 1);
  printf("%d\n", post[r_post]);
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &post[i]);
  memcpy(in, post, sizeof(post));
  std::sort(in + 1, in + n + 1);
  solve(1, n, 1, n);
}
