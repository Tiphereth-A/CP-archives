const int N = 505, M = 62505, INF = 0x3f3f3f3f;
int s, t, maxflow, cnt = 1, parity[2][N], head[N], dis[N], cur[N];
string a[N];
struct Edge {
    int u, v, w, next;
} edge[M];
int Parity(const string &x) {
    int res = 0;
    for (int i = 0; x[i] != '\0'; i++)
        for (int j = i + 1; x[j] != '\0'; j++)
            if (x[i] > x[j]) res ^= 1;
    return res;
}
bool is_swappable(const string &x, const string &y) {
    int res = 0;
    for (int i = 0; x[i] != '\0'; i++)
        if (x[i] != y[i]) res++;
    return res == 2;
}
void add(int u, int v, int w) {
    edge[++cnt] = {u, v, w, head[u]};
    head[u] = cnt;
}
int dfs(int u, int lim) {
    if (!lim || u == t) return lim;
    int flow = 0, f;
    for (int i = cur[u]; i; i = edge[i].next) {
        int v = edge[i].v, w = edge[i].w;
        cur[u] = i;
        if (dis[v] == dis[u] + 1 && (f = dfs(v, min(lim, w)))) {
            flow += f;
            lim -= f;
            edge[i].w -= f;
            edge[i ^ 1].w += f;
            if (!lim) break;
        }
    }
    return flow;
}
bool bfs() {
    queue<int> q;
    for (int i = s; i <= t; i++) {
        cur[i] = head[i];
        dis[i] = INF;
    }
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].v, w = edge[i].w;
            if (dis[v] >= INF && w) {
                dis[v] = dis[u] + 1;
                if (v == t) return 1;
                q.push(v);
            }
        }
    }
    return dis[t] < INF;
}
void dinic() {
    while (bfs()) maxflow += dfs(s, INF);
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int p = Parity(a[i]);
        parity[p][++parity[p][0]] = i;
    }
    for (int i = 1; i <= parity[0][0]; i++)
        for (int j = 1; j <= parity[1][0]; j++) {
            if (is_swappable(a[parity[0][i]], a[parity[1][j]])) {
                add(parity[0][i], parity[1][j], 1);
                add(parity[1][j], parity[0][i], 0);
            }
        }
    s = 0, t = n + 1;
    for (int i = 1; i <= parity[0][0]; i++) {
        add(s, parity[0][i], 1);
        add(parity[0][i], s, 0);
    }
    for (int i = 1; i <= parity[1][0]; i++) {
        add(parity[1][i], t, 1);
        add(t, parity[1][i], 0);
    }
    dinic();
    cout << n - maxflow << endl;
    return 0;
}
