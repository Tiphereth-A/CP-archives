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
#define maxn 10010
using namespace std;
bool c[105];
int main() {
    int n;
    cin >> n;
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != i) c[j] = !c[j];
            cout << c[j];
        }
        cout << endl;
    }
    return 0;
}
