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
const int N = 3e4 + 5;
long long V, n, v[N], w[N], f[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> V >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
        v[i] *= w[i];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = V; j; --j) {
            if (j >= w[i])
                f[j] = std::max(f[j], f[j - w[i]] + v[i]);
        }
    cout << f[V];
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}