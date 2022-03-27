#include <cstdio>
#include <stack>
#if 0
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#endif
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rg register
#define il inline
#define tpn typename
#if 0
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 63, sizeof(a))
#define memax(a) memset(a, 127, sizeof(a))
#define gc getchar
#define sstr stringstream
#endif
#define M 10005
#define N 1005
const int INF = 0x7fffffff;
int num[M], n, c, m, slen, pos = 1;
std::stack<int> sta;
int main() {
    scanf("%d%d", &n, &c);
    fp(i, 1, n) scanf("%d", num + i);
    while (sta.size() + m < n) {
        slen = sta.size();
        int minn = INF, l = pos, len = c - slen;
        for (int j = l; j < l + len && j <= n; j++) {
            if (num[j] < minn) {
                minn = num[j];
                pos = j;
            }
        }
        if (sta.empty() || minn <= sta.top()) {
            for (int j = l; j <= pos; j++) sta.push(num[j]);
            ++pos;
        } else
            pos = l;
        printf("%d ", sta.top());
        m++;
        sta.pop();
    }
    while (!sta.empty()) {
        printf("%d ", sta.top());
        sta.pop();
    }
    return 0;
}