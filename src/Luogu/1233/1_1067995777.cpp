#include <algorithm>
#include <cstdio>
#define N 5005
#define fp(i, l, r) for (register int(i) = (l); (i) <= (r); ++(i))
#define gi(a) do {
register char ch;
while ((a = getchar()) > '9' || a < '0')
    ;
for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; a = (a << 3) + (a << 1) + ch - '0')
    ;
}
while (0)
    struct node {
        int l, w;
    } a[N];
int n, f[N], ans;
bool cmp(node &a, node &b) { return (a.l == b.l) ? (a.w > b.w) : (a.l > b.l); }
int main() {
    gi(n);
    fp(i, 1, n) {
        gi(a[i].l);
        gi(a[i].w);
    }
    std::sort(a + 1, a + n + 1, cmp);
    fp(i, 1, n) {
        int tmp = a[i].w;
        if (tmp > f[ans])
            f[++ans] = tmp;
        else {
            int l = 1, r = ans, mid;
            while (l < r) {
                mid = ((r - l) >> 1) + l;
                (f[mid] >= tmp) ? (r = mid) : (l = mid + 1);
            }
            f[l] = tmp;
        }
    }
    printf("%d", ans);
    return 0;
}