#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define MAXN 1005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int main() {
    string s;
    cin >> s;
    int len = s.size(), ans = s.size() - 1;
    _for(i, 1, len - 1)
        if (s[i] == s[i - 1]) ans--;
    if (s[len - 1] == '0') ans++;
    cout << ans;
    return 0;
}