#include <bits/stdc++.h>
#define M 200005
#define N 1005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 63, sizeof(a))
#define memax(a) memset(a, 127, sizeof(a))
#define gc getchar
#define tpn typename
#if 0
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
template <tpn A> inline A Max(const A &x,const A &y){
    return x>y?x:y;
}
template <tpn A> inline A Min(const A &x,const A &y){
    return x<y?x:y;
}
template <tpn A> inline void Swap(A &x,A &y){
    x^=y,y^=x,x^=y;
}
template <tpn A> inline A Abs(const A &x){
    return x>0?x:-x;
}
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
using namespace std;
int n;
struct bt {
    char data, l, r;
} f[1000];
void print(char data) {
    if (data == '*') return;
    _for(i, 1, n) {
        if (f[i].data == data) {
            cout << f[i].data;
            print(f[i].l);
            print(f[i].r);
            return;
        }
    }
}
int main() {
    cin >> n;
    _for(i, 1, n) cin >> f[i].data >> f[i].l >> f[i].r;
    print(f[1].data);
    return 0;
}