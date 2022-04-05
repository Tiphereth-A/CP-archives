#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#define rg register
#define il inline
#define M 200005
#define N 1005
#define INF 0x7fffffff
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 63, sizeof(a))
#define memax(a) memset(a, 127, sizeof(a))
#define gc getchar
#define tpn typename
#if 1
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
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
template <tpn A, tpn B>
inline void read(A &a, B &b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
#endif
using namespace std;
int n, a, b, k[N], ans[N];
queue<int> q;
void bfs() {
    int now;
    while (!q.empty()) {
        now = q.front();
        if (now == b) break;
        q.pop();
        int next = now + k[now];
        if (next >= 1 && next <= n && (ans[next] == -1)) {
            ans[next] = ans[now] + 1;
            q.push(next);
        }
        next = now - k[now];
        if (next >= 1 && next <= n && (ans[next] == -1)) {
            ans[next] = ans[now] + 1;
            q.push(next);
        }
    }
    if (!q.empty())
        printf("%d", ans[now]);
    else
        printf("-1");
}
int main() {
    read(n, a, b);
    memset(ans, -1, sizeof(ans));
    fp(i, 1, n) read(k[i]);
    q.push(a);
    ans[a] = 0;
    bfs();
    return 0;
}