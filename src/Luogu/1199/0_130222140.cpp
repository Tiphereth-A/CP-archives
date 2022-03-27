#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
const int N = 505;
int n, a[N][N];
bool chosen[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
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
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}