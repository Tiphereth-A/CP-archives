#include <bits/stdc++.h>
using namespace std;
void f(string p, string i) {
  if (p.empty()) return;
  char root = p[0];
  int k = i.find(root);
  p.erase(p.begin());
  f(p.substr(0, k), i.substr(0, k));
  f(p.substr(k), i.substr(k + 1));
  cout << root;
}
int main() {
  string p, i;
  cin >> i >> p;
  f(p, i);
  return 0;
}
