#include <algorithm>
#include <cstdio>
#include <cstring>
#define N 1005
#define D 100000000
#define fp(i, l, r) for (register int(i) = (l); (i) <= (r); ++(i))
#define fd(i, l, r) for (register int(i) = (l); (i) >= (r); --(i))
#define il inline
#define rg register
#define ll long long
#define ull unsigned long long
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define gi(a) do {
register char ch;
while ((a = getchar()) > '9' || a < '0')
    ;
for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; a = (a << 3) + (a << 1) + ch - '0')
    ;
}
while (0)
    struct node {
        int a, b;
        ll mul;
    } p[N];
struct bign {
#define M 5005
    ll num[M], len;
    bign() {
        memset(num, 0, sizeof(num));
        len = 1;
    }
} ans, final, c;
int n;
bool cmp(node a, node b) {
    return a.mul < b.mul;
}
il void mul(int m) {
    fp(i, 1, ans.len) ans.num[i] *= m;
    fp(i, 1, ans.len) {
        ll* tmp = ans.num + i;
        if (*tmp >= D) {
            *(tmp + 1) += *tmp / D;
            *tmp %= D;
        }
        if (i == ans.len && *(tmp + 1)) ++ans.len;
    }
}
il void div(int d) {
    ull q = 0LL;
    memset(c.num, 0, sizeof(c.num));
    c.len = ans.len;
    fd(i, c.len, 1) {
        q *= D;
        q += ans.num[i];
        c.num[i] = q / d;
        q %= d;
    }
    while (c.len > 1 && !c.num[c.len])
        --c.len;
}
il bool comp() {
    if (c.len > final.len)
        return 1;
    if (c.len < final.len)
        return 0;
    fd(i, c.len, 1) {
        if (c.num[i] > final.num[i])
            return 1;
        if (c.num[i] < final.num[i])
            return 0;
    }
}
int main() {
    gi(n);
    fp(i, 0, n) {
        gi(p[i].a);
        gi(p[i].b);
        p[i].mul = p[i].a;
        p[i].mul *= p[i].b;
    }
    std::sort(p + 1, p + n + 1, cmp);
    ans.num[1] = 1;
    fp(i, 1, n) {
        mul(p[i - 1].a);
        div(p[i].b);
        if (comp()) {
            memset(final.num, 0, sizeof(final.num));
            final = c;
        }
    }
    printf("%d", final.num[final.len]);
    fd(i, final.len - 1, 1) printf("%08d", final.num[i]);
    return 0;
}