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
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
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
#define INF 0x3f3f3f3f
map<char, string> morse;
map<string, string> dict;
int cmp(const string &a, const string &b) {
    if (a == b) return 0;
    if (a.size() > b.size()) {
        if (b == a.substr(0, b.size())) return a.size() - b.size();
    } else if (a == b.substr(0, a.size()))
        return b.size() - a.size();
    return INF;
}
string solve(const string &str) {
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