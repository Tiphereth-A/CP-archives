#include <cstdio>
#include <cstring>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memp(a) memset(a, 1, sizeof(a))
#define memn(a) memset(a, -1, sizeof(a))
#define tpn typename
template <tpn A>
inline A Max(const A& x, const A& y) {
    return x > y ? x : y;
}
template <tpn A>
inline void Swap(A& x, A& y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline void read(A& x) {
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
inline void read(A& a, B& b, C& c) {
    read(a), read(b), read(c);
}
const int M = 200005;
struct deque {
    int val[M], pos[M];
    int head, tail;
    deque() {
        mem(val);
        mem(pos);
        head = 1;
        tail = 0;
    }
} q;
int n, l, r, a[M], f[M], ans;
int main() {
    read(n, l, r);
    if (l > r) Swap(l, r);
    fp(i, 0, n) read(a[i]);
    fd(i, n, n - l + 1) f[i] = a[i];
    fd(i, n + 1, l) {
        while (q.tail >= q.head && f[i] > q.val[q.tail]) --q.tail;
        ++q.tail;
        q.val[q.tail] = f[i];
        q.pos[q.tail] = i;
        f[i - l] = q.val[q.head] + a[i - l];
        if (i + r == q.pos[q.head]) ++q.head;
    }
    printf("%d\n", f[0]);
    return 0;
}