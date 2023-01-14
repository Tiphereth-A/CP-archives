#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int a, b;
    cin >> a >> b;
    cout << "Circus Act " << i << ":" << endl
         << (a == 1 || 5 * a <= 2 * b ? "Chester can do it!" :
                                        "Chester will fail!")
         << endl;
    if (i != n) cout << endl;
  }
  return 0;
}
