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
const int dx[] = {1, 2, 2, 1}, dy[] = {2, 1, -1, -2};
using std::cin;
using std::cout;
int n, m;
int ans;
void dfs(int now_x, int now_y) {
    if (now_x == m && now_y == n) {
        ++ans;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int xx = now_x + dx[i], yy = now_y + dy[i];
        if (xx < 0 || xx > m || yy < 0 || yy > n)
            continue;
        dfs(xx, yy);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> n >> m;
    dfs(0, 0);
    std::cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}