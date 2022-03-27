#include <algorithm>
#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
int x[30], n;
int main() {
    scanf("%d", &n);
    fp(i, 1, n) {
        x[i] = i;
        printf("%5.d", i);
    }
    while (std::next_permutation(x + 1, x + 1 + n)) {
        puts("");
        fp(i, 1, n) printf("%5.d", x[i]);
    }
}