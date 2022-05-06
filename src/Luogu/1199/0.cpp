#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 505;
int n, a[N][N];
bool chosen[N];
int main() {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    cin >> n;
    int ans = 0;
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    for (int i = 1; i <= n; ++i) {
        std::sort(a[i] + 1, a[i] + n + 1, std::greater<int>());
        if (a[i][2] > ans)
            ans = a[i][2];
    }
    cout << 1 << endl
         << ans;
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}