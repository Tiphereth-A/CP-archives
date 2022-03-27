#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define maxn 405
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
string s1, s2, a1, a2;
int cnt[3];
il int cmp(string& a, string& b) {
    if (a == "[]") {
        if (b == "()")
            return 1;
        else if (b == "8<")
            return 2;
        else
            return 0;
    } else if (a == "8<") {
        if (b == "[]")
            return 1;
        else if (b == "()")
            return 2;
        else
            return 0;
    } else {
        if (b == "8<")
            return 1;
        else if (b == "[]")
            return 2;
        else
            return 0;
    }
}
int main() {
    getline(cin, s1);
    getline(cin, s2);
    int l = s1.size() - 1;
    for (int i = 0; i <= l; i += 2) {
        a1 = s1.substr(i, 2);
        a2 = s2.substr(i, 2);
        cnt[cmp(a1, a2)]++;
    }
    if (cnt[1] > cnt[2])
        cout << "TEAM 1 WINS";
    else if (cnt[1] < cnt[2])
        cout << "TEAM 2 WINS";
    else
        cout << "TIE";
    return 0;
}
