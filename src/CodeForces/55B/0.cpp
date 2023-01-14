#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int frac[] = {1, 1, 2, 6, 24};
char oper[3];
long long dfs(int total_num, long long *__num) {
  if (total_num == 1) return *__num;
  long long num[total_num];
  int id_num[total_num];
  int tmp = frac[total_num];
  long long tmp_r = 0x3f3f3f3f3f3f3f3fll;
  for (int i = 0; i < total_num; ++i) id_num[i] = i;
  do {
    for (int i = 0; i < total_num; ++i) num[i] = __num[id_num[i]];
    long long a = num[0], b = num[1];
    num[1] = (oper[4 - total_num] == '+') ? a + b : a * b;
    tmp_r = std::min(tmp_r, dfs(total_num - 1, num + 1));
    std::next_permutation(id_num, id_num + total_num);
  } while (--tmp);
  return tmp_r;
}
int main() {
  long long __num[4];
  cin >> __num[0] >> __num[1] >> __num[2] >> __num[3];
  cin >> oper[0] >> oper[1] >> oper[2];
  cout << dfs(4, __num);
  return 0;
}
