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
    int n, k;
    cin >> n >> k;
    cout << n + (n - 1) / (k - 1);
    return 0;
}