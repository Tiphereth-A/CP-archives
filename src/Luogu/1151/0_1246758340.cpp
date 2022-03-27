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
#define MAXN 1005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int k;
int main() {
    bool f = 1;
    cin >> k;
    fp(i, 10000, 30000) if ((i / 100 % k == 0) && (i / 10 % 1000 % k == 0) && (i % 1000 % k == 0)) printf("%d\n", i), f = 0;
    if (f) cout << "No";
    return 0;
}