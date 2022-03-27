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
typedef unsigned long long u64;
using std::cin;
using std::cout;
using std::endl;
const int N = 1e4 + 5;
int n;
std::priority_queue<u64, std::vector<u64>, std::greater<u64>> q;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> n;
    for (int a, i = 1; i <= n; i++) {
        cin >> a;
        q.push(a);
    }
    u64 ans = 0;
    while (q.size() > 1) {
        u64 a = q.top();
        q.pop();
        u64 b = q.top();
        q.pop();
        ans += a + b;
        q.push(a + b);
    }
    cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}