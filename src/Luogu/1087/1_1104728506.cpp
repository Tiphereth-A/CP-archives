#include <bits/stdc++.h>
#include <bits/stdc++.h>*/
#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
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
string s;
char c[4] = {'B', 'I', 'B', 'F'};
int n;
void f(string s, int l) {
    if (l >= 0) {
        if (l >= 1) {
            int t = (s.find('1') != string::npos) + ((s.find('0') != string::npos) << 1);
            int subl = (1 << (l - 1));
            f(s.substr(0, subl), l - 1);
            f(s.substr(subl), l - 1);
            cout << c[t];
        } else {
            cout << c[s[0] & 1];
        }
    }
    return;
}
void f(int l, int len) {
    if (len >= 0) {
        if (len >= 1) {
            int t = ((s.find('1', l) - len) >= 0) + (((s.find('0', l) - len) >= 0) << 1);
            int sublen = (1 << (len - 1));
            f(l, len - 1);
            f(sublen, len - 1);
            cout << c[t];
        } else {
            cout << c[s[l] & 1];
        }
    }
    return;
}
int main() {
    cin >> n >> s;
    f(s, n);
    return 0;
}