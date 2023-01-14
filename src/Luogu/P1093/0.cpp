#include <bits/stdc++.h>
using namespace std;
struct stu {
  int chi, math, eng, sum, id;
} m[310];
bool cmp(stu a, stu b) {
  if (a.sum == b.sum) {
    if (a.chi == b.chi) return a.id < b.id;
    return a.chi > b.chi;
  }
  return a.sum > b.sum;
}
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> m[i].chi >> m[i].math >> m[i].eng;
    m[i].sum = m[i].chi + m[i].math + m[i].eng;
    m[i].id = i + 1;
  }
  sort(m, m + n, cmp);
  for (int i = 0; i < 5; i++) cout << m[i].id << ' ' << m[i].sum << endl;
  return 0;
}
