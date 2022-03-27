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
#define M 5005
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
int pre[M];
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
il void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy)
        pre[fx] = fy;
}
int main() {
    int n = gi(), m = gi(), p = gi();
    fp(i, 1, n) pre[i] = i;
    while (m--) {
        int x = gi(), y = gi();
        merge(x, y);
    }
    while (p--) {
        int x = gi(), y = gi();
        int fx = find(x), fy = find(y);
        if (fx == fy)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}