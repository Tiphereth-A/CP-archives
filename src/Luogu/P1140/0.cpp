#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 100 + 5;
const int sim[5][5] = {{5, -1, -2, -1, -3},
                       {-1, 5, -3, -2, -4},
                       {-2, -3, 5, -2, -2},
                       {-1, -2, -2, 5, -1},
                       {-3, -4, -2, -1, 0}};
int get_sim(char a, char b) {
  return sim[(a == 'A') ? 0 :
             (a == 'C') ? 1 :
             (a == 'G') ? 2 :
             (a == 'T') ? 3 :
                          4][(b == 'A') ? 0 :
                             (b == 'C') ? 1 :
                             (b == 'G') ? 2 :
                             (b == 'T') ? 3 :
                                          4];
}
std::string a(" "), b(" ");
int len_a, len_b;
int f[N][N];
int main() {
  std::string tmp_a, tmp_b;
  cin >> len_a >> tmp_a >> len_b >> tmp_b;
  a += tmp_a;
  b += tmp_b;
  for (int now_a = 1; now_a <= len_a; ++now_a)
    memset(f[now_a] + 1, 0x80, sizeof(f[now_a]) - sizeof(int));
  for (int now_a = 1; now_a <= len_a; ++now_a)
    f[now_a][0] = f[now_a - 1][0] + get_sim(a[now_a], 0);
  for (int now_b = 1; now_b <= len_b; ++now_b)
    f[0][now_b] = f[0][now_b - 1] + get_sim(0, b[now_b]);
  for (int now_a = 1; now_a <= len_a; ++now_a)
    for (int now_b = 1; now_b <= len_b; ++now_b) {
      f[now_a][now_b] = std::max(
        std::max(f[now_a][now_b],
                 f[now_a - 1][now_b - 1] + get_sim(a[now_a], b[now_b])),
        std::max(f[now_a - 1][now_b] + get_sim(a[now_a], 0),
                 f[now_a][now_b - 1] + get_sim(0, b[now_b])));
    }
  cout << f[len_a][len_b];
  return 0;
}
