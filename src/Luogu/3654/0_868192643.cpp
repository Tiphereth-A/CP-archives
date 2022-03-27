#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define gc getchar
using namespace std;
const int M = 100005;
const int N = 105;
const int INF = 0x7fffffff;
int r, c, k, ans;
char g[N][N];
int main() {
    scanf("%d%d%d", &r, &c, &k);
    gc();
    fp(i, 1, r) fp(j, 1, c) cin >> g[i][j];
    fp(i, 1, c) {
        int cnt = 0;
        fp(j, 1, r + 1) {
            if (g[j][i] == '.')
                cnt++;
            else {
                if (cnt >= k) ans += cnt - k + 1;
                cnt = 0;
            }
        }
    }
    fp(i, 1, r) {
        int cnt = 0;
        fp(j, 1, c + 1) {
            if (g[i][j] == '.')
                cnt++;
            else {
                if (cnt >= k) ans += cnt - k + 1;
                cnt = 0;
            }
        }
    }
    printf("%d", ((k == 1) ? (ans >> 1) : (ans)));
    return 0;
}