#include <cstdio>
int main() {
    int x;
    scanf("%d", &x);
    printf("%d", !(x % 400) || (x % 100 && !(x % 4)));
}