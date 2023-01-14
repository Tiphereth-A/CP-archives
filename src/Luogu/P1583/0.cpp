#include <bits/stdc++.h>
using namespace std;
struct n {
  int id;
  int num;
};
bool cmp(n a, n b) {
  if (a.num == b.num) return a.id < b.id;
  return a.num > b.num;
}
int main() {
  int n, k;
  cin >> n >> k;
  int e[11];
  struct n w[20010];
  for (int i = 1; i <= 10; i++) cin >> e[i];
  for (int i = 0; i < n; i++) {
    cin >> w[i].num;
    w[i].id = i + 1;
  }
  sort(w, w + n, cmp);
  for (int i = 0; i < n; i++) w[i].num += e[i % 10 + 1];
  sort(w, w + n, cmp);
  for (int i = 0; i < k; i++) cout << w[i].id << ' ';
  return 0;
}
