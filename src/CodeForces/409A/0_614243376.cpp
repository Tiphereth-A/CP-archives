#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 405
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
string s1, s2, a1, a2;
int cnt[3];
inline int cmp(string &a, string &b) {
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
