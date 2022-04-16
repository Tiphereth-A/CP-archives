#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define M 30005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
string str;
int n;
int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    _rfor(i, str.size() - 1, 1) {
        n *= 10;
        n += str[i] - '0';
    }
    if (str[0] == '-')
        n = -n;
    else {
        n *= 10;
        n += str[0] - '0';
    }
    while (n % 10 == 0) n /= 10;
    cout << n;
    return 0;
}
