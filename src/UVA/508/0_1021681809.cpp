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
#define rg register
#define rgi register int
#define il inline
#define FP(i, l, r) for (register int i = (l); i <= (r); ++i)
#define REP(i, l, r) for (register int i = (l); i < (r); ++i)
#define FD(i, r, l) for (register int i = (r); i >= (l); --i)
#define REPR(i, r, l) for (register int i = (r); i > (l); --i)
#define gc getchar
#define tpn typename
#define INS(a) std::inserter((a), (a).begin())
#define ALL(a) (a).begin(), (a).end()
#define sstream std::stringstream
#ifdef __C_LIB__
#define MEM(a) memset(a, 0, sizeof(a))
#define MEMID(a) memset(a, 0x3f, sizeof(a))
#define MEMNG(a) memset(a, 0xff, sizeof(a))
#endif
#ifdef __CPP_STYLE__
#define DEBUG(x) std::cout << #x << " = " << x << std::endl
#else
#define DEBUG(type, x) printf(#x "=%" #type "\n", (x))
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef double db;
typedef long double ldb;
#endif
#ifndef tpn
#define tpn typename
#endif
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
#define M 310
#define INF 0x3f3f3f3f
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int N = 1e6 + 5;
map<char, string> morse;
map<string, string> dict;
int cmp(const string& a, const string& b) {
    if (a == b) return 0;
    if (a.size() > b.size()) {
        if (b == a.substr(0, b.size())) return a.size() - b.size();
    } else if (a == b.substr(0, a.size()))
        return b.size() - a.size();
    return INF;
}
string solve(const string& str) {
    string ans = "";
    int lMin = INF;
    for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        int tmp = cmp(str, it->second);
        if (!tmp && !lMin && *ans.rbegin() != '!') {
            ans += "!";
            return ans;
        } else if (tmp <= lMin)
            ans = it->first;
        lMin = Min(lMin, tmp);
    }
    if (lMin) ans += "?";
    return ans;
}
int main() {
    string str, ch;
    while (cin >> ch && ch != "*") {
        cin >> str;
        morse[ch[0]] = str;
    }
    while (cin >> str && str != "*") {
        ch.clear();
        REP(i, 0, str.length())
        ch += morse[str[i]];
        dict[str] = ch;
    }
    while (cin >> str && str != "*") cout << solve(str) << endl;
    return 0;
}