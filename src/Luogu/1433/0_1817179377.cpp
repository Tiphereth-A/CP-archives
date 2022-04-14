#include <bits/stdc++.h>*/
#include <bits/stdc++.h>
#define M 200005
#define N 1001
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define tpn typename
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
#if 0
template <tpn A> inline void read(A &x){
    char c;
    A neg=1;
    do{
        c=getchar();
    }while ((c<'0'||c>'9')&&c!='-');
    if (c=='-') neg=-1,c=getchar();
    x=0;
    do{
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }while (c>='0'&&c<='9');
    x*=neg;
}
template <tpn A,tpn B> inline void read(A &a,B &b){
read(a),read(b);}
template <tpn A,tpn B,tpn C> inline void read(A &a,B &b,C &c){
read(a),read(b),read(c);}
template <tpn A,tpn B,tpn C,tpn D> inline void read(A &a,B &b,C &c,D &d){
read(a),read(b),read(c),read(d);}
#endif
db x[N], y[N], d[N][N], ans = 1234567890.0;
int n, v[N];
void dfs(int step, int now, db l) {
    if (l > ans) return;
    if (step == n) {
        ans = Min(ans, l);
        return;
    }
    _for(i, 1, n)
        if (!v[i]) {
            v[i] = 1;
            dfs(step + 1, i, l + d[now][i]);
            v[i] = 0;
        }
}
int main() {
    scanf("%d", &n);
    _for(i, 1, n) scanf("%lf%lf", &x[i], &y[i]);
    _for(i, 0, n)
        _for(j, 0, n) d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    dfs(0, 0, 0.0);
    printf("%.2lf", ans);
    return 0;
}