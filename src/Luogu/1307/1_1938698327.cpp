#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define M 30005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
string str;
int n;
int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    fd(i, str.size() - 1, 1) {
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
