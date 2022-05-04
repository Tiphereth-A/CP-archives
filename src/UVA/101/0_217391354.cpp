#define __C_STYLE__
#define __C_LIB__
#define __CPP_STYLE__
#define __CPP_LIB__
#define __STL__
#define __DEF__
#define __STD__
#define __FASTIO__
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
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
#define REPLU(i, l, r) for (long unsigned int i = (l); i < (r); ++i)
#define gc getchar
#endif
#ifdef __CPP_STYLE__
#define SYNC std::ios::sync_with_stdio(false)
#define DEBUG(x) std::cout << #x << " = " << x << std::endl
#else
#define DEBUG(type, x) printf(#x "=%" #type "\n", (x))
#endif
#endif
#ifndef typename
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
#ifndef typename
#endif
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
#else
namespace fastIO {
#define gc() (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], obuff[SIZ], *oS = obuff, *oT = oS + SIZ - 1, fu[110], c;
int fr;
inline void out() {
    fwrite(obuff, 1, oS - obuff, stdout);
    oS = obuff;
}
template <class Type>
inline void read(Type &x) {
    Type y = 1;
    for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc())
        ;
    c == '-' ? y = -1 : x = (c & 15);
    for (c = gc(); c >= '0' && c <= '9'; c = gc())
        x = x * 10 + (c & 15);
    x *= y;
}
template <class Type>
inline void print(Type x, char text = '\n') {
    if (x < 0)
        *oS++ = '-', x *= -1;
    if (x == 0)
        *oS++ = '0';
    while (x)
        fu[++fr] = x % 10 + '0', x /= 10;
    while (fr)
        *oS++ = fu[fr--];
    *oS++ = text;
    out();
}
}  // namespace fastIO
using namespace fastIO;
#endif
#endif
const int N = 30;
int n;
vector<int> pile[N];
void findPos(int a, int &p, int &h) {
    REP(i, 0, n)
    REPLU(j, 0, pile[i].size())
    if (pile[i][j] == a) {
        p = i;
        h = j;
        return;
    }
}
void clr(int p, int h) {
    REPLU(i, h + 1, pile[p].size()) {
        int tmp = pile[p][i];
        pile[tmp].push_back(tmp);
    }
    pile[p].resize(h + 1);
}
void pil(int p, int h, int b) {
    REPLU(i, h, pile[p].size())
    pile[b].push_back(pile[p][i]);
    pile[p].resize(h);
}
void print() {
    REP(i, 0, n) {
        cout << i << ":";
        REPLU(j, 0, pile[i].size())
        cout << ' ' << pile[i][j];
        cout << endl;
    }
}
int main() {
    SYNC;
    cin >> n;
    REP(i, 0, n)
    pile[i].push_back(i);
    string s1, s2;
    int a, b;
    while (cin >> s1 >> a >> s2 >> b) {
        int pa, pb, ha, hb;
        findPos(a, pa, ha);
        findPos(b, pb, hb);
        if (pa == pb) continue;
        if (s1 == "move") clr(pa, ha);
        if (s2 == "onto") clr(pb, hb);
        pil(pa, ha, pb);
    }
    print();
    return 0;
}