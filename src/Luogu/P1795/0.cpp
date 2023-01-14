#include <bits/stdc++.h>
typedef long long ll;
#define MAXN 44725
using namespace std;
ll d[MAXN];
int f(int low, int high, int t) {
  while (low <= high) {
    int mid = (low + high) / 2;
    if (d[mid] > t) high = mid - 1;
    else if (d[mid] < t) low = mid + 1;
    else return mid;
  }
  return -1;
}
int main() {
  ll t = 1;
  for (int i = 1; t <= 1000000000; i++) {
    t = (i * i - i + 2) / 2;
    d[i] = t;
  }
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    long t;
    scanf("%ld", &t);
    if (f(1, 44725, t) == -1) printf("0\n");
    else printf("1\n");
  }
  return 0;
}
