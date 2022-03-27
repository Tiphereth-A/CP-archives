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
#define M 10005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int a, b, c;
int main() {
    scanf("%d%d%d", &a, &b, &c);
    if (c > a + b)
        printf("%d", a + b + 1);
    else if (b > a + c)
        printf("%d", a + c + 1);
    else if (a > c + b)
        printf("%d", c + b + 1);
    else
        printf("%d", (a + b + c + 3) / 2);
    return 0;
}