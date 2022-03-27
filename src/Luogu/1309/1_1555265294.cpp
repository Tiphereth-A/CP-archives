#include <algorithm>
#include <cstdio>
#define N 200005
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef long long i64;
i64 id[N], win[N], lose[N];
i64 rank[N], w[N];
int n, r, q;
int wincnt, losecnt;
bool inline cmp(int a, int b) { return (rank[a] == rank[b]) ? (a < b) : (rank[a] > rank[b]); }
void inline merge() {
    int i = 1, j = 1;
    int cnt = 0;
    while (i <= wincnt && j <= losecnt) id[++cnt] = cmp(win[i], lose[j]) ? win[i++] : lose[j++];
    while (i <= wincnt) id[++cnt] = win[i++];
    while (j <= losecnt) id[++cnt] = lose[j++];
}
int main() {
    scanf("%d%d%d", &n, &r, &q);
    n <<= 1;
    fp(i, 1, n) {
        scanf("%lld", rank + i);
        id[i] = i;
    }
    fp(i, 1, n) scanf("%lld", w + i);
    std::sort(id + 1, id + n + 1, cmp);
    while (r--) {
        wincnt = losecnt = 0;
        for (register int i = 1; i <= n; i += 2) {
            if (w[id[i]] > w[id[i + 1]]) {
                ++rank[id[i]];
                win[++wincnt] = id[i];
                lose[++losecnt] = id[i + 1];
            } else {
                ++rank[id[i + 1]];
                win[++wincnt] = id[i + 1];
                lose[++losecnt] = id[i];
            }
        }
        merge();
    }
    printf("%lld", id[q]);
    return 0;
}
