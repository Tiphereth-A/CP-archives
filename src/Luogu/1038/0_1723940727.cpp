#include <bits/stdc++.h>
using namespace std;
using db = double;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const int OFFSET = 5;
const int N = 100 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
struct Edge {
    int w, to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
    e[++cnt_edge] = {w, y, head[x]};
    head[x] = cnt_edge;
}
int in[N], out[N];
i64 neu[N];
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    int n, p;
    scanf("%d%d", &n, &p);
    queue<int> q;
    i64 c, u;
    _for(i, 1, n) {
        scanf("%lld%lld", &c, &u);
        if (c) {
            q.push(i);
            neu[i] = c;
        } else
            neu[i] = c - u;
    }
    int x, y;
    i64 w;
    _for(i, 1, p) {
        scanf("%d%d%lld", &x, &y, &w);
        addEdge(x, y, w);
        ++in[y];
        ++out[x];
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (neu[now] <= 0) continue;
        for (int i = head[now], to; i; i = e[i].next) {
            neu[to = e[i].to] += e[i].w * neu[now];
            if (!(--in[to])) q.push(to);
        }
    }
    bool f = 1;
    _for(i, 1, n)
        if (!out[i] && (neu[i] > 0)) {
            f = 0;
            printf("%d %lld\n", i, neu[i]);
        }
    if (f) puts("NULL");
FINISHED:
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}