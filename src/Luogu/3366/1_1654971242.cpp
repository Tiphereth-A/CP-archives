#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define swap(a, b) (a) ^= (b) ^= (a) ^= (b)
#define gi getint
#define gc getchar
using namespace std;
struct graph {
    int x, y, z;
} g[200005];
int pre[5005];
il int find(int x) {
    int a = x, b = x, c;
    while (a != pre[a]) a = pre[a];
    while (b != pre[b]) {
        c = pre[b];
        pre[b] = a;
        b = c;
    }
    return a;
}
il int getint() {
    rg int t = 0;
    rg char c = gc();
    while (c < 48 || c > 57)
        c = gc();
    while (c >= 48 && c <= 57) {
        t = (t << 3) + (t << 1) + (c ^ 48);
        c = gc();
    }
    return t;
}
bool cmp(graph a, graph b) {
    return a.z < b.z;
}
int main() {
    int n = gi(), m = gi(), cnt = 0, ans = 0;
    fp(i, 1, m) {
        g[i].x = gi();
        g[i].y = gi();
        g[i].z = gi();
    }
    fp(i, 1, n) pre[i] = i;
    sort(g + 1, g + m + 1, cmp);
    fp(i, 1, m) {
        if (cnt == n - 1) break;
        int fx = find(g[i].x), fy = find(g[i].y);
        if (fx != fy) {
            ans += g[i].z;
            pre[fx] = fy;
            ++cnt;
        }
    }
    if (cnt < n - 1)
        cout << "orz";
    else
        cout << ans;
    return 0;
}