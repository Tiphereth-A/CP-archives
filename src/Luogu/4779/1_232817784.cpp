#include <cstdio>
#include <queue>
#define rg register
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define INF_I32 0x7fffffff
const int M = 500005;
const int N = 100005;
struct edge {
    int next, to, val;
} e[M];
struct node {
    int u, val;
    bool operator<(const node &a) const {
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