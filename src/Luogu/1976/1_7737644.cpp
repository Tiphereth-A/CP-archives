#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
int h[3005] = {1};
int main() {
    int n;
    scanf("%d", &n);
    fp(i, 0, n) fp(j, i + 1, n) h[j] = (h[j] + h[j - 1]) % 100000007;
    printf("%d", h[n]);
    return 0;
}