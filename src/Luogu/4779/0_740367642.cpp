#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#ifdef __C_STYLE__
#include <cstdio>
#endif
#ifdef __C_LIB__
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#endif
#ifdef __STL__
#include <algorithm>
#include <deque>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#endif
#ifdef __DEF__
#define rg register
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define _replu(i, l, r) for (register long unsigned int i = (l); i < (r); ++i)
#define _fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define _repr(i, r, l) for (register int i = (r); i > (l); --i)
#define _gc getchar
#define _pc putchar
#define tpn typename
typedef long long i64;
typedef unsigned long long u64;
#endif
#define INF_I32 0x7fffffff
const int M = 500005;
const int N = 100005;
struct edge {
    int next, to, val;
} e[M];
struct node {
    int u, val;
    bool operator<(const node& a) const {
        return val > a.val;
    }
};
int head[N], cnt;
il void add(int u, int v, int val) {
    e[++cnt] = {head[u], v, val};
    head[u] = cnt;
}
int n, m, s, dis[N];
il void dijkstra(int s) {
    _fp(i, 1, n) dis[i] = INF_I32;
    dis[s] = 0;
    std::priority_queue<node> pq;
    pq.push((node){s, 0});
    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        int uNow = now.u, valNow = now.val;
        if (valNow != dis[uNow]) continue;
        int disU = dis[uNow];
        for (rg int i = head[uNow]; i; i = e[i].next) {
            int v = e[i].to, val = e[i].val;
            if (disU + val < dis[v]) {
                dis[v] = disU + val;
                pq.push((node){v, dis[v]});
            }
        }
    }
    _fp(i, 1, n) printf("%d ", dis[i]);
}
int main() {
    scanf("%d%d%d", &n, &m, &s);
    int u, v, w;
    _fp(i, 1, m) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    dijkstra(s);
    return 0;
}