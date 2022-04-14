#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define M 5005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define swap(a, b) (a) ^= (b) ^= (a) ^= (b)
#define gi getint
#define gc getchar
using namespace std;
int pre[M];
inline int getint() {
    int t = 0;
    char c = gc();
    while (c < 48 || c > 57)
        c = gc();
    while (c >= 48 && c <= 57) {
        t = (t << 3) + (t << 1) + (c ^ 48);
        c = gc();
    }
    return t;
}
inline int find(int x) {
    int a = x, b = x, c;
    while (a != pre[a]) a = pre[a];
    while (b != pre[b]) {
        c = pre[b];
        pre[b] = a;
        b = c;
    }
    return a;
}
inline void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy)
        pre[fx] = fy;
}
int main() {
    int n = gi(), m = gi(), p = gi();
    _for(i, 1, n) pre[i] = i;
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