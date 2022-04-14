#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 1e4 + 5;
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[fa[fa[fa[x]]]]); }
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    int n, m;
    while ((cin >> n) && n) {
        cin >> m;
        int ans = n - 1;
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        for (int x, y, i = 1; i <= m; ++i) {
            cin >> x >> y;
            int fx = find(x), fy = find(y);
            if (fx != fy) {
                fa[fx] = fy;
                --ans;
            }
        }
        cout << ans << endl;
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}