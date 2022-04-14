#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define maxn 405
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
double x, y, sum;
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    _for(i, 1, n) {
        cin >> x >> y;
        sum += y;
    }
    sum /= n;
    sum += 5;
    printf("%.3lf", sum);
    return 0;
}
