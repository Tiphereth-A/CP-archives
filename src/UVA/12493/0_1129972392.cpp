#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define SZ(x) ((int)(x).size())
#define ALL(v) (v).begin(), (v).end()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define reveach(i, v) for (__typeof((v).rbegin()) i = (v).rbegin(); i != (v).rend(); ++i)
#define REP(i, n) for (int i = 1; i <= int(n); i++)
#define rep(i, n) for (int i = 0; i < int(n); i++)
using namespace std;
typedef long long ll;
#define X first
#define Y second
typedef pair<int, int> pii;
typedef pair<pii, pii> PII;
template <class T>
inline bool RD(T& ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
template <class T>
inline void PT(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) PT(x / 10);
    putchar(x % 10 + '0');
}
int euler(int n) {
    int ans = n;
    int num = n;
    for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            ans = ans / i * (i - 1);
            while (num % i == 0) num /= i;
        }
    }
    if (num > 1) ans = ans / num * (num - 1);
    return ans;
}
int main() {
    int n;
    while (~scanf("%d", &n)) {
        printf("%d\n", euler(n) / 2);
    }
}