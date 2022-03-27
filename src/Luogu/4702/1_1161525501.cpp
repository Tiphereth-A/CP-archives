#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
int n, a;
unsigned long long sum;
int main() {
    scanf("%d", &n);
    fp(i, 1, n) {
        scanf("%d", &a);
        sum += a;
    }
    if (sum & 1)
        printf("Alice");
    else
        printf("Bob");
    return 0;
}
