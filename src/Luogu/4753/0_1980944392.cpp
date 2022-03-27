#include <algorithm>
#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
int m, n, s, w[100010];
int pos, cnt, stp[100010];
bool f[100010];
int main() {
    scanf("%d%d%d", &n, &m, &s);
    fp(i, 1, m) scanf("%d", w + i);
    std::sort(w + 1, w + m + 1);
    w[m + 1] = n;
    fp(i, 1, m + 1) {
        if (w[i] - pos >= s) {
            pos = w[i];
            stp[++cnt] = i;
            f[i] = true;
        }
    }
    if (pos != w[m + 1]) {
        puts("NO");
        return 0;
    }
    fd(i, m, 0) {
        if (!f[i] && pos - w[i] >= s) {
            pos = w[i];
            stp[++cnt] = i;
            f[i] = true;
        }
    }
    if (cnt < m + 2)
        puts("NO");
    else {
        puts("YES");
        fp(i, 1, m + 2) printf("%d%c", stp[i], i == m + 2 ? '\n' : ' ');
    }
    return 0;
}