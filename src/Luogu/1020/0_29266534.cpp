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
const int N = 1e5 + 5;
int f1[N], f2[N], cnt1 = 1, cnt2 = 1;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    int tmp;
    scanf("%d", &tmp);
    f1[1] = f2[1] = tmp;
    while (~scanf("%d", &tmp)) {
        if (tmp <= f1[cnt1])
            f1[++cnt1] = tmp;
        else
            f1[std::upper_bound(f1 + 1,
                                f1 + cnt1 + 1,
                                tmp,
                                std::greater<int>()) -
               f1] = tmp;
        if (tmp > f2[cnt2])
            f2[++cnt2] = tmp;
        else
            f2[std::lower_bound(f2 + 1,
                                f2 + cnt2 + 1,
                                tmp) -
               f2] = tmp;
    }
    printf("%d\n%d", cnt1, cnt2);
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}