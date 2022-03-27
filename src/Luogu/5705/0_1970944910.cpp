#include <cstdio>
int main() {
    char a, b, c, d;
    scanf("%c%c%c.%c", &a, &b, &c, &d);
    printf("%c.%c%c%c", d, c, b, a);
}