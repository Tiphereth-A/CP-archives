#include <bits/stdc++.h>
using namespace std;
int num[1000];
char str[1000];
int main() {
  int n;
  cin >> n;
  cin >> str;
  int l = strlen(str);
  for (int i = 0; i < l; i++) num[i] = str[i] - '0';
  for (int i = 1; i <= n * 2 + 3; i++) {
    for (int j = 0; j < l; j++) {
      for (int k = 1; k <= 3 + n; k++) {
        if (k == 3 + n) {
          printf("\x20");
        } else {
          if (i == 1) {
            if (k == 1 || k == 2 + n) {
              printf("\x20");
            } else {
              if (num[j] != 1 && num[j] != 4) {
                cout << "-";
              } else {
                printf("\x20");
              }
            }
          }
          if (i >= 2 && i <= 1 + n) {
            if (k >= 2 && k <= 1 + n) {
              printf("\x20");
            } else {
              if (num[j] == 5 || num[j] == 6) {
                if (k == 1) {
                  cout << "|";
                } else {
                  printf("\x20");
                }
              } else if (num[j] == 1 || num[j] == 2 || num[j] == 3 ||
                         num[j] == 7) {
                if (k == 1) {
                  printf("\x20");
                } else {
                  cout << "|";
                }
              } else {
                cout << "|";
              }
            }
          }
          if (i == n + 2) {
            if (num[j] == 1 || num[j] == 7 || num[j] == 0) {
              printf("\x20");
            } else {
              if (k == 1 || k == 2 + n) {
                printf("\x20");
              } else {
                cout << "-";
              }
            }
          }
          if (i >= n + 3 && i <= n * 2 + 2) {
            if (k >= 2 && k <= 1 + n) {
              printf("\x20");
            } else {
              if (num[j] == 1 || num[j] == 3 || num[j] == 4 || num[j] == 5 ||
                  num[j] == 7 || num[j] == 9) {
                if (k == 1) {
                  printf("\x20");
                } else {
                  cout << "|";
                }
              } else if (num[j] == 2) {
                if (k == 1) {
                  cout << "|";
                } else {
                  printf("\x20");
                }
              } else {
                cout << "|";
              }
            }
          }
          if (i == n * 2 + 3) {
            if (k == 1 || k == 2 + n) {
              printf("\x20");
            } else {
              if (num[j] == 1 || num[j] == 4 || num[j] == 7) {
                printf("\x20");
              } else {
                cout << "-";
              }
            }
          }
        }
      }
    }
    cout << endl;
  }
  return 0;
}
