#include <bits/stdc++.h>
#define M 1000001
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
string str[101], o;
int t, l;
int getint(int &x, string c) {
  int res = 0, l = c.size();
  while ((c[x] < '0' || c[x] > '9') && x < l) {
    if (c[x] == 'n') {
      x++;
      return M;
    }
    x++;
  }
  while (c[x] >= '0' && c[x] <= '9') {
    res *= 10;
    res += c[x] - '0';
    x++;
  }
  return res;
}
int getcomp() {
  int res = 0, x = 3;
  if (o[2] == 'n') res = getint(x, o);
  return res;
}
int check(int n) {
  int res = 0, errf = -1, now = 0, st, et, x;
  stack<int> s;
  bool alpha[26] = {0}, ctbt[26] = {0};
  _for(i, 1, l) {
    if (str[i][0] == 'F') {
      int k = str[i][2] - 'a';
      if (alpha[k]) return -1;
      s.push(k);
      alpha[k] = true;
      x = 4;
      st = getint(x, str[i]);
      et = getint(x, str[i]);
      if (et - st > 1000) {
        if (errf == -1) {
          now++;
          ctbt[k] = true;
          res = max(res, now);
        }
      }
      if (st > et) {
        if (errf = -1) errf = k;
      }
    } else {
      if (s.empty()) return -1;
      int k = s.top();
      s.pop();
      alpha[k] = false;
      if (errf == k) errf = -1;
      if (ctbt[k]) {
        ctbt[k] = false;
        now--;
      }
    }
  }
  if (s.size()) return -1;
  else return res;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d ", &l);
    getline(cin, o);
    _for(i, 1, l) getline(cin, str[i]);
    int w = getcomp();
    int ans = check(w);
    if (ans == -1) printf("ERR\n");
    else if (ans == w) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
