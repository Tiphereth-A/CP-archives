#define __CPP_STYLE__
#define __DEF__
#define __STD__
#include <bits/stdc++.h>
#ifdef __STD__
using namespace std;
#endif
#ifdef __DEF__
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
#endif
#ifdef __CPP_STYLE__
#define SYNC std::ios::sync_with_stdio(false)
#endif
#endif
template <typename A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <typename A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <typename A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <typename A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
#ifdef __FASTIO__
#if 1
template <typename A>
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
template <typename A, typename B>
inline void read(A &a, B &b) {
    read(a), read(b);
}
template <typename A, typename B, typename C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
#endif
const int N = 1010;
int n, m, t;
map<int, int> team;
queue<int> q, q1[N];
string op;
int main() {
    SYNC;
    cin >> n >> m;
    int a;
    REP(i, 0, n) {
        cin >> a;
        team[i] = a;
    }
    cin >> t;
    while (t--) {
        cin >> op;
        if (op[1] == 'u') {
            int tmp;
            cin >> tmp;
            int tmpt = team[tmp];
            if (q1[tmpt].empty()) q.push(tmpt);
            q1[tmpt].push(tmp);
        } else {
            int tmpt = q.front();
            cout << q1[tmpt].front() << endl;
            q1[tmpt].pop();
            if (q1[tmpt].empty()) q.pop();
        }
    }
    return 0;
}