#include <algorithm>
#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define il inline
#define gi(a) do {
register char ch;
while ((a = getchar()) > '9' || a < '0')
    ;
for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; a = a * 10 + ch - '0')
    ;
}
while (0)
#define M 200005
    struct xjbq {
        int num, cnt;
    } a[M], vis[M];
int n, tot;
bool cmp(const xjbq &a, const xjbq &b) {
    return a.num < b.num;
}
il void hash(const int &num) {
    int key = num % M;
    while (vis[key].cnt && vis[key].num != num) key++;
    if (!vis[key].cnt) vis[key].num = num;
    vis[key].cnt++;
}
int main() {
    gi(n);
    fp(i, 1, n) {
        int b;
        gi(b);
        hash(b);
    }
    fp(i, 0, M - 1) if (vis[i].cnt) a[++tot] = vis[i];
    std::sort(a + 1, a + tot + 1, cmp);
    fp(i, 1, tot) printf("%d %d\n", a[i].num, a[i].cnt);
    return 0;
}