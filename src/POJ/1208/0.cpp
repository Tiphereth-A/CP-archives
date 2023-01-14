#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int n;
vector<int> vec[35];
void _rfor(int a, int &p, int &h) {
  for (p = 0; p < n; ++p)
    for (h = 0; h < vec[p].size(); ++h)
      if (vec[p][h] == a) return;
}
void clr(int p, int h) {
  for (int i = h + 1; i < vec[p].size(); ++i) {
    int b = vec[p][i];
    vec[b].push_back(b);
  }
  vec[p].resize(h + 1);
}
void po(int p, int h, int p2) {
  for (int i = h; i < vec[p].size(); ++i) vec[p2].push_back(vec[p][i]);
  vec[p].resize(h);
}
int main() {
  cin >> n;
  string s1, s2;
  for (int i = 0; i < n; ++i) vec[i].push_back(i);
  int a, b;
  while (cin >> s1 >> a >> s2 >> b) {
    int pa, pb, ha, hb;
    _rfor(a, pa, ha);
    _rfor(b, pb, hb);
    if (pa == pb) continue;
    if (s2 == "onto") clr(pb, hb);
    if (s1 == "move") clr(pa, ha);
    po(pa, ha, pb);
  }
  for (int i = 0; i < n; ++i) {
    printf("%d:%c", i, " \n"[!vec[i].size()]);
    for (int j = 0; j < vec[i].size(); j++)
      printf("%d%c", vec[i][j], " \n"[j == vec[i].size() - 1]);
  }
  return 0;
}
