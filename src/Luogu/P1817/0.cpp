#include <bits/stdc++.h>
using namespace std;
const long long maps[][10] = {
  {0},
  {0, 1, 2, 3, 4, 5, 6, 7},
  {0, 1, 6, 15, 28, 45, 66, 91, 120},
  {0, 2, 15, 52, 143, 350, 799, 1744, 3695},
  {0, 3, 28, 143, 614, 2431, 9184, 33603, 120090},
  {0, 4, 45, 350, 2431, 16000, 102147, 637330, 3903895},
  {0, 5, 66, 799, 9184, 102147, 1114394, 11948355, 126244104},
  {0, 6, 91, 1744, 33603, 637330, 11948355, 220762028, 4028145967}};
int main() {
  int m, n;
  cin >> m >> n;
  cout << maps[m][n] * 2;
}
