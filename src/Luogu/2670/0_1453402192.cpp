#include <iostream>
using namespace std;
bool a[110][110];
int n, m;
char tmp;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (register int i = 1; i <= n; ++i) {
        for (register int j = 1; j <= m; ++j) {
            cin >> tmp;
            if (tmp == '*') a[i][j] = 1;
        }
    }
    for (register int i = 1; i <= n; ++i) {
        for (register int j = 1; j <= m; ++j) {
            if (a[i][j] == 1)
                cout << '*';
            else
                cout << a[i + 1][j + 1] + a[i + 1][j - 1] + a[i + 1][j] + a[i][j + 1] + a[i][j - 1] + a[i - 1][j + 1] + a[i - 1][j] + a[i - 1][j - 1];
        }
        cout << endl;
    }
    return 0;
}