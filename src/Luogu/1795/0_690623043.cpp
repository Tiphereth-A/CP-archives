#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define maxn 44725
using namespace std;
ll d[maxn];
int f(int low, int high, int t) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (d[mid] > t)
            high = mid - 1;
        else if (d[mid] < t)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
int main() {
    ll t = 1;
    for (int i = 1; t <= 1000000000; i++) {
        t = (i * i - i + 2) / 2;
        d[i] = t;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        long t;
        scanf("%ld", &t);
        if (f(1, 44725, t) == -1)
            printf("0\n");
        else
            printf("1\n");
    }
    return 0;
}
