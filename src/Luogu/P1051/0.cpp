#include <bits/stdc++.h>
using namespace std;
struct stu {
  string name;
  int s1, s2;
  char f1, f2;
  int p;
  int sch;
} m[110];
int main() {
  int n, MAXN = -1, sum = 0, j = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> m[i].name >> m[i].s1 >> m[i].s2 >> m[i].f1 >> m[i].f2 >> m[i].p;
    if (m[i].s1 > 80 && m[i].p > 0) m[i].sch += 8000;
    if (m[i].s1 > 85 && m[i].s2 > 80) m[i].sch += 4000;
    if (m[i].s1 > 90) m[i].sch += 2000;
    if (m[i].s1 > 85 && m[i].f2 == 'Y') m[i].sch += 1000;
    if (m[i].s2 > 80 && m[i].f1 == 'Y') m[i].sch += 850;
    sum += m[i].sch;
    if (MAXN < m[i].sch) {
      MAXN = m[i].sch;
      j = i;
    }
  }
  cout << m[j].name << endl << MAXN << endl << sum;
  return 0;
}
