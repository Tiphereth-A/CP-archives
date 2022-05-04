#include <bits/stdc++.h>
#define gc getchar
template <typename A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <typename A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <typename A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <typename A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
#if 0
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
using namespace std;
char c;
stack<int> s;
int a, b;
int main() {
    while ((c = gc()) != '@') {
        switch (c) {
            case '+': {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a + b);
                a = 0;
                break;
            }
            case '-': {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b - a);
                a = 0;
                break;
            }
            case '*': {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a * b);
                a = 0;
                break;
            }
            case '/': {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b / a);
                a = 0;
                break;
            }
            case '.': {
                s.push(a);
                a = 0;
                break;
            }
            default: {
                a = a * 10 + c - '0';
            }
        }
    }
    cout << s.top();
    return 0;
}