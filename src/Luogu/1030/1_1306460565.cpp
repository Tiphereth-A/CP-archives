#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>*/
#include <map>
#include <queue>
#include <stack>
#include <string>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 63, sizeof(a))
#define memax(a) memset(a, 127, sizeof(a))
#define gc getchar
#define tpn typename
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
template <tpn A>
inline A Max(const A& x, const A& y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A& x, const A& y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A& x, A& y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A& x) {
    return x > 0 ? x : -x;
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
template <tpn A, tpn B>
inline void read(A& a, B& b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A& a, B& b, C& c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A& a, B& b, C& c, D& d) {
    read(a), read(b), read(c), read(d);
}
#endif
using namespace std;
string in, af;
void pre(string in, string af) {
    if (in.size() > 0) {
        char c = af[af.size() - 1];
        cout << c;
        int r = in.find(c);
        pre(in.substr(0, r), af.substr(0, r));
        pre(in.substr(r + 1), af.substr(r, in.size() - r - 1));
    }
}
int main() {
    cin >> in >> af;
    pre(in, af);
    return 0;
}