#include <cstdio>
typedef long long i64;
const int M = 20005;
#define _for(i, l, r) for (register int i = (l); i <= (r); i++)
#define _fp(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
int f[M], n, V, v[35];
int main() {
    scanf("%d%d", &V, &n);
    _for(i, 1, n) scanf("%d", &v[i]);
    _for(i, 1, n) _fp(j, V, 0) if (j - v[i] >= 0) f[j] =
                      max(f[j], f[j - v[i]] + v[i]);
    int ans = 0;
    _for(i, 1, V) ans = max(ans, f[i]);
    printf("%d", V - ans);
    return 0;
}
