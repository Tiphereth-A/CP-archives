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
int l, r;
using namespace std;
int main() {
    char c;
    cin >> c;
    while (c != '@') {
        if (c == '(')
            l++;
        else if (c == ')')
            r++;
        if (r > l) {
            cout << "NO";
            return 0;
        }
        cin >> c;
    }
    if (l == r)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}