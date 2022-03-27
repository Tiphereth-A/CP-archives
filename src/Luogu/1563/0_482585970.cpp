#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define maxn 100010
using namespace std;
struct people {
    short f;
    string s;
} p[maxn];
int main() {
    int n, m, a, s, now = 1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i].f >> p[i].s;
    for (int i = 1; i <= m; i++) {
        cin >> a >> s;
        if (p[now].f + a == 1)
            now += s;
        else
            now -= s;
        if (now <= 0) now += n;
        if (now >= n) now = (now - 1) % n + 1;
    }
    cout << p[now].s;
    return 0;
}
