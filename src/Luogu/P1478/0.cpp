#include <bits/stdc++.h>
using namespace std;
typedef struct apple {
  int x;
  int y;
} apple;
bool cmp(apple a, apple b) { return a.y < b.y; }
int main() {
  int n, s, a, b, ans;
  cin >> n >> s >> a >> b;
  int h = a + b;
  vector<apple> array(n);
  for (int i = 0; i < n; i++) cin >> array[i].x >> array[i].y;
  sort(array.begin(), array.end(), cmp);
  for (int i = 0; i < n; i++) {
    if (s >= array[i].y && h >= array[i].x) {
      ans++;
      s -= array[i].y;
    }
  }
  cout << ans;
  return 0;
}
