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
    int num[maxn];
    for (int i = 0; i < n; i++)
        cin >> num[i];
    sort(num, num + n);
    int ans = unique(num, num + n) - num;
    if (ans > k)
        cout << num[k - 1];
    else
        cout << "NO RESULT";
    return 0;
}
