#include <bits/stdc++.h>
#define N 205
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#if 0
template <typename A> inline A Max(const A &x,const A &y){
    return x>y?x:y;
}
template <typename A> inline A Min(const A &x,const A &y){
    return x<y?x:y;
}
template <typename A> inline void Swap(A &x,A &y){
    x^=y,y^=x,x^=y;
}
template <typename A> inline A Abs(const A &x){
    return x>0?x:-x;
}
template <typename A> inline void read(A &x){
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
template <typename A,typename B> inline void read(A &a,B &b){
read(a),read(b);}
template <typename A,typename B,typename C> inline void read(A &a,B &b,C &c){
read(a),read(b),read(c);}
template <typename A,typename B,typename C,typename D> inline void read(A &a,B &b,C &c,D &d){
read(a),read(b),read(c),read(d);}
#endif
bool v[N];
int main() {
    int n, m, tot = 0;
    scanf("%d%d", &n, &m);
    _for(i, 1, n) {
        _for(j, 1, m) {
            if (++tot > n) tot = 1;
            if (v[tot]) j--;
        }
        printf("%d ", tot);
        v[tot] = 1;
    }
    return 0;
}