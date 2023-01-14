#include <bits/stdc++.h>
using namespace std;
int main() {
  string w, t;
  getline(cin, w);
  getline(cin, t);
  for (int i = 0; i < w.length(); i++) w[i] = tolower(w[i]);
  for (int i = 0; i < t.length(); i++) t[i] = tolower(t[i]);
  w = ' ' + w + ' ';
  t = ' ' + t + ' ';
  if (t.find(w) == string::npos) cout << -1;
  else {
    int p = t.find(w);
    int q = t.find(w), num = 0;
    while (q != string::npos) {
      num++;
      q = t.find(w, q + 1);
    }
    cout << num << ' ' << p;
  }
  return 0;
}
