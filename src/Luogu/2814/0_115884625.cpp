#define __C_LIB__
#define __CPP_STYLE__
#define __CPP_LIB__
#define __STL__
#define __DEF__
#define __FUNC__
#ifdef __C_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __C_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __STL__
#include <bits/stdc++.h>
#endif
#ifdef __DEF__
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define tpn typename
#ifdef __C_LIB__
#endif
#ifdef __CPP_STYLE__
#define SYNC std::ios::sync_with_stdio(false)
#define _debug(x) std::cout << #x << " = " << x << std::endl
#else
#define _debug(type, x) printf(#x "=%" type "\n", (x))
#endif
typedef double db;
#endif
#ifdef __FUNC__
#ifndef tpn
#define tpn typename
#endif
template <tpn A>
inline A Max(const A &x, const A &y) { return x > y ? x : y; }
template <tpn A>
inline A Min(const A &x, const A &y) { return x < y ? x : y; }
template <tpn A>
inline void Swap(A &x, A &y) { x ^= y ^= x ^= y; }
template <tpn A>
inline A Abs(const A &x) { return x > 0 ? x : -x; }
template <tpn A>
inline A Gcd(A x, A y) { return !y ? x : Gcd(y, x % y); }
#endif
const int M = 5e5 + 5;
const int N = 50005;
const int MOD = 998244353;
const db EPS = 1e-6;
std::string str;
char op;
std::map<std::string, int> m;
std::string diag[N];
int mem_num, fa_id;
int fa[N];
int find(int x) { return x == fa[x] ? x : x = find(fa[x]); }
int main() {
    SYNC;
    _for(i, 1, 50000) fa[i] = i;
    while ((std::cin >> op >> str) && op != '$') {
        if (!m[str]) {
            m[str] = ++mem_num;
            diag[mem_num] = str;
        }
        if (op == '#')
            fa_id = m[str];
        else if (op == '+')
            fa[m[str]] = fa_id;
        else if (op == '?')
            std::cout << str << ' ' << diag[find(m[str])] << std::endl;
    }
    return 0;
}