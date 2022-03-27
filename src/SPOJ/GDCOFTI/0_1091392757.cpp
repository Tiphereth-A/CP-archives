#include <algorithm>
#include <iostream>
#include <math.h>
#define ull unsigned long long
using namespace std;
ull a, b, c;
int main() {
    cin >> a >> b >> c;
    printf("%lld", __gcd(a, __gcd(b, c)));
    return 0;
}