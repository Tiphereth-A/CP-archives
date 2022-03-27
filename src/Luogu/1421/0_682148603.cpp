#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    float a, b;
    int c;
    cin >> a >> b;
    a += b / 10;
    a /= 1.9;
    c = a;
    printf("%d", c);
    return 0;
}