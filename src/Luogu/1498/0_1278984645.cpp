#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
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
#define swap(a, b) (a) ^= (b) ^= (a) ^= (b)
#define gi getint
#define gc getchar
using namespace std;
int n;
char c[1024][2048];
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    int l = 4, flo = 1;
    fp(i, 0, 1023) fp(j, 0, 2047) c[i][j] = '\x20';
    c[0][0] = c[1][1] = '/';
    c[0][1] = c[0][2] = '_';
    c[0][3] = c[1][2] = '\\';
    while (flo < n) {
        int h = l >> 1;
        fp(i, 0, h - 1) fp(j, 0, l - 1)
            c[i + h][j + h] = c[i][j + l] = c[i][j];
        l <<= 1;
        flo++;
    }
    fd(i, (l >> 1) - 1, 0) {
        fp(j, 0, l - 1) cout << c[i][j];
        cout << endl;
    }
    return 0;
}