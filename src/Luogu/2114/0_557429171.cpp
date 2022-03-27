#include <cstdio>
#include <cstring>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
int r1 = 0x7fffffff, r0, ans;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    char op[5] = "";
    int t;
    fp(i, 1, n) {
        scanf("%s%d", op, &t);
        if (*op == 'A') {
            r1 &= t;
            r0 &= t;
        } else if (*op == 'O') {
            r1 |= t;
            r0 |= t;
        } else {
            r1 ^= t;
            r0 ^= t;
        }
    }
    fd(i, 30, 0) {
        if (r0 & (1 << i))
            ans += 1 << i;
        else if (m >= (1 << i) && (r1 & (1 << i))) {
            m -= 1 << i;
            ans += 1 << i;
        }
    }
    printf("%d", ans);
    return 0;
}