#include <cstdio>
#define ll long long
#define fp(i, l, r) for (register ll i = (l); i <= (r); i++)
ll h[20];
int main() {
    ll n;
    scanf("%lld", &n);
    fp(i, 0, n) h[i] = 1;
    fp(i, 1, n) fp(j, i, n) if (i != j) h[j] += h[j - 1];
    printf("%lld", h[n]);
    return 0;
}