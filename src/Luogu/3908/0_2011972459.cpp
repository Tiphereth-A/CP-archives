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
int main() {
    ull n;
    cin >> n;
    switch (n & 3) {
        case 0: {
            cout << n;
            break;
        }
        case 1: {
            cout << 1;
            break;
        }
        case 2: {
            cout << n + 1;
            break;
        }
        case 3: {
            cout << 0;
            break;
        }
    }
    return 0;
}
