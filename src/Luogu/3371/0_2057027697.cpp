#include <cstdio>
#include <queue>
#include <stack>
#define ctn continue
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define memn(a) memset(a, -1, sizeof(a))
#define meminf(a) memset(a, 0x7fffffff, sizeof(a))
#define gc getchar
#define tpn typename
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <tpn A>
inline void read(A &x) {
    char c;
    A neg = 1;
    do {
        c = getchar();
    } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') neg = -1, c = getchar();
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    } while (c >= '0' && c <= '9');
    x *= neg;
}
template <tpn A, tpn B, tpn C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
const int M = 500005;
const int N = 10005;
const int INF = 0x7fffffff;
int n, m, s, head[N], cnt, ans[N];
bool vis[N];
struct s {
    int v, w, nxt;
} e[M];
void add(int u, int v, int w) {
    e[++cnt].nxt = head[u];
    e[cnt].v = v;
    e[cnt].w = w;
    head[u] = cnt;
}
void spfa() {
    std::queue<int> q;
    fp(i, 1, n) ans[i] = INF;
    q.push(s);
    ans[s] = 0;
    vis[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (ans[v] > ans[now] + e[i].w) {
                ans[v] = ans[now] + e[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}
int main() {
    read(n, m, s);
    fp(i, 1, m) {
        int u, v, w;
        read(u, v, w);
        add(u, v, w);
    }
    spfa();
    fp(i, 1, n) printf("%d ", ans[i]);
    return 0;
}
