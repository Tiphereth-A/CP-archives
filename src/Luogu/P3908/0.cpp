#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
int main() {
  ull n;
  cin >> n;
  switch (n & 3) {
    case 0: {
      cout << n;
      break;
    }
    case 1: {
      cout << 1;
      break;
    }
    case 2: {
      cout << n + 1;
      break;
    }
    case 3: {
      cout << 0;
      break;
    }
  }
  return 0;
}
