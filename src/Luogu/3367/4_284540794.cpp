#include <cstdio>
#include <iostream>
#define rg register
#define il inline
#define M 10005
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int pre[M];
il int find(int x) {
    int a = x;
    while (a != pre[a])
        a = pre[a];
    int b = x, c;
    while (b != a) {
        c = pre[b];
        pre[b] = a;
        b = c;
    }
    return a;
}
il void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy)
        pre[fx] = fy;
}
int main() {
    int n, m;
    cin >> n >> m;
    fp(i, 1, n) pre[i] = i;
    fp(i, 1, m) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1)
            merge(x, y);
        else {
            int fx = find(x), fy = find(y);
            if (fx == fy)
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}