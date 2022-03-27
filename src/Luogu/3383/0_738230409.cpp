#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
#define rg register
#define il inline
#define maxn 10000010
using namespace std;
bool noprime[maxn];
int p[maxn], f[maxn];
void get_prime(int m) {
    int pnum = 0;
    for (int i = 2; i < m; i++) {
        if (!noprime[i])
            p[pnum++] = i;
        for (int j = 0; j < pnum && i * p[j] < m; j++) {
            noprime[i * p[j]] = true;
            if (i % p[j] == 0)
                break;
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    get_prime(n + 1);
    noprime[1] = 1;
    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);
        (!noprime[a]) ? printf("Yes\n") : printf("No\n");
    }
    return 0;
}