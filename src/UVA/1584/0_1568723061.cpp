#include <cstdio>
#include <cstring>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define pc putchar
#define N 105
int t;
char s[N];
inline bool cmp(int len, int a, int b) {
    fp(i, 0, len - 1) if (s[(i + a) % len] != s[(i + b) % len]) return s[(i + a) % len] < s[(i + b) % len];
    return 0;
}
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int len = strlen(s), ans = 0;
        fp(i, 1, len - 1) if (cmp(len, i, ans)) ans = i;
        fp(i, 0, len - 1) pc(s[(ans + i) % len]);
        pc('\n');
    }
    return 0;
}