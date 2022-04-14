#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define M 20005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int f[M], n, V, v[35];
inline int getint() {
    int t = 0;
    char c = gc();
    while (c < 48 || c > 57) c = gc();
    while (c >= 48 && c <= 57) {
        t = t * 10 + c - 48;
        c = gc();
    }
    return t;
}
int main() {
    V = gi();
    n = gi();
    _for(i, 1, n) v[i] = gi();
    _for(i, 1, n)
        _rfor(j, V, 0)
            if (j - v[i] >= 0) f[j] = max(f[j], f[j - v[i]] + v[i]);
    int ans = 0;
    _for(i, 1, V) ans = max(ans, f[i]);
    cout << V - ans;
    return 0;
}
