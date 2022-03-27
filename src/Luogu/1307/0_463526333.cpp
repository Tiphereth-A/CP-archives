#include <iostream>
#include <string>
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
using namespace std;
string str;
int n;
int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    fd(i, str.size() - 1, 1) {
        n *= 10;
        n += str[i] - '0';
    }
    if (str[0] == '-')
        n = -n;
    else {
        n *= 10;
        n += str[0] - '0';
    }
    while (n % 10 == 0) n /= 10;
    cout << n;
    return 0;
}
