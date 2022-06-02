#define __C_STYLE__
#define __C_LIB__
#define __CPP_STYLE__
#define __CPP_LIB__
#define __STL__
#define __DEF__
#define __STD__
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
#ifdef __CPP_STYLE__
#include <iostream>
#endif
#ifdef __CPP_LIB__
#include <fstream>
#include <iomanip>
#include <string>
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
#ifdef __STD__
using namespace std;
#endif
#ifdef __DEF__
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
int n, cnt;
int main() {
    SYNC;
    while (cin >> n && n) {
        int a, b;
        map<int, int> team;
        cout << "Scenario #" << ++cnt << endl;
        _for(i, 1, n) {
            cin >> a;
            while (a--) {
                cin >> b;
                team[b] = i;
            }
        }
        queue<int> q, q1[N];
        string op;
        while (cin >> op && op[0] != 'S') {
            if (op[0] == 'E') {
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
        cout << endl;
    }
    return 0;
}