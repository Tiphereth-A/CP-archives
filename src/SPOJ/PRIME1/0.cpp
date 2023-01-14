#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
bool isprime(int x) {
  if (x == 1) return false;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0) return false;
  return true;
}
int main() {
  int n, a, b;
  int j;
  scanf("%d", &n);
  while (n--) {
    scanf("%d%d", &a, &b);
    for (j = a; j <= b; j++) {
      if (isprime(j)) printf("%d\n", j);
    }
    printf("\n");
  }
  return 0;
}
