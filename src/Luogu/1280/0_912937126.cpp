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
const int N = 1e4 + 5;
int n, k;
struct node {
    int l, time;
    bool operator<(const node& oth) const { return l > oth.l; }
} task[N];
int f[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> n >> k;
    for (int i = 1; i <= k; ++i)
        cin >> task[i].l >> task[i].time;
    std::sort(task + 1, task + k + 1);
    int j = 1;
    for (int i = n; i; --i) {
        if (i != task[j].l)
            f[i] = f[i + 1] + 1;
        else
            while (task[j].l == i)
                f[i] = std::max(f[i], f[i + task[j++].time]);
    }
    cout << f[1];
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}