#include <iostream>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define M 1005
int n;
char tmp, llt[M][M];
bool m[M][M];
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    fp(i, 1, n) fp(j, 1, n) {
        cin >> tmp;
        if (tmp == 'O') m[i][j] = true;
    }
    fp(i, 1, n) fp(j, 1, n) cin >> llt[i][j];
    fp(i, 1, n) fp(j, 1, n) if (m[i][j]) cout << llt[i][j];
    fp(i, 1, n) fd(j, n, 1) if (m[j][i]) cout << llt[i][n - j + 1];
    fd(i, n, 1) fd(j, n, 1) if (m[i][j]) cout << llt[n - i + 1][n - j + 1];
    fd(i, n, 1) fp(j, 1, n) if (m[j][i]) cout << llt[n - i + 1][j];
    return 0;
}