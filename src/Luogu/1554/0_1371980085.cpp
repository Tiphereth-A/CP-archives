#include <iostream>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
using namespace std;
int m, n, cnt[10];
int main() {
    cin >> m >> n;
    fp(i, m, n) {
        int a = i;
        while (a) {
            cnt[a % 10]++;
            a /= 10;
        }
    }
    fp(i, 0, 9) cout << cnt[i] << ' ';
    return 0;
}