#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define MAXN 1005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int cnt, n;
void search(int num) {
    if (num > n)
        return;
    else
        cnt++;
    search(num * 10);
    search(num * 10 + 1);
}
int main() {
    cin >> n;
    search(1);
    cout << cnt;
    return 0;
}