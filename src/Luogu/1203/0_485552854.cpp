#include <iostream>
#include <string>
#define il inline
#define rg register
using namespace std;
string str;
int n;
il int max(int& a, int& b) {
    return (a > b) ? a : b;
}
il int min(int& a, int& b) {
    return (a < b) ? a : b;
}
il int fnd(int x) {
    int ans = 0;
    char a = str[x], b = str[x + 1];
    for (rg int i = x;; --i) {
        char tmp = str[i];
        if (tmp == a || tmp == 'w')
            ++ans;
        else
            break;
    }
    for (rg int i = x + 1;; ++i) {
        char tmp = str[i];
        if (tmp == b || tmp == 'w')
            ++ans;
        else
            break;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> str;
    str = str + str + str;
    int ans = -1;
    for (rg int i = n; i < (n << 1); ++i) {
        char* tmp = &str[i];
        if (*tmp == *(tmp + 1))
            continue;
        if (*tmp == 'w') {
            *tmp = 'r';
            ans = max(ans, fnd(i));
            *tmp = 'b';
            ans = max(ans, fnd(i));
            *tmp = 'w';
        }
        ans = max(ans, fnd(i));
    }
    ans = (~ans) ? min(ans, n) : n;
    cout << ans << endl;
    return 0;
}