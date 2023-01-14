#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int i[10], ans = 0, a[177176][10];
  memset(a, 0, sizeof(a));
  for (i[0] = 1; i[0] < 4; i[0]++)
    for (i[1] = 1; i[1] < 4; i[1]++)
      for (i[2] = 1; i[2] < 4; i[2]++)
        for (i[3] = 1; i[3] < 4; i[3]++)
          for (i[4] = 1; i[4] < 4; i[4]++)
            for (i[5] = 1; i[5] < 4; i[5]++)
              for (i[6] = 1; i[6] < 4; i[6]++)
                for (i[7] = 1; i[7] < 4; i[7]++)
                  for (i[8] = 1; i[8] < 4; i[8]++)
                    for (i[9] = 1; i[9] < 4; i[9]++)
                      if (i[0] + i[1] + i[2] + i[3] + i[4] + i[5] + i[6] +
                            i[7] + i[8] + i[9] ==
                          n) {
                        ans++;
                        a[ans][0] = i[0];
                        a[ans][1] = i[1];
                        a[ans][2] = i[2];
                        a[ans][3] = i[3];
                        a[ans][4] = i[4];
                        a[ans][5] = i[5];
                        a[ans][6] = i[6];
                        a[ans][7] = i[7];
                        a[ans][8] = i[8];
                        a[ans][9] = i[9];
                      }
  cout << ans << endl;
  for (int j = 1; j <= ans; j++) {
    for (int k = 0; k < 9; k++) cout << a[j][k] << ' ';
    cout << a[j][9] << endl;
  }
  return 0;
}
