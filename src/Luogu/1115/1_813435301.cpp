#include <bits/stdc++.h>
#define M 200005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define tpn typename
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
int f[M], a[M], n, ans = -999999;
int main() {
    scanf("%d", &n);
    _for(i, 1, n) {
        scanf("%d", &f[i]);
        a[i] = Max(a[i - 1] + f[i], f[i]);
        ans = Max(ans, a[i]);
    }
    printf("%d", ans);
    return 0;
}