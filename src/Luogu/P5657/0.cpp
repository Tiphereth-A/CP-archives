#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
int n;
u64 k;
int main() {
  cin >> n >> k;
  k ^= k >> 1;
  while (~--n) cout << (k >> n & 1);
}
