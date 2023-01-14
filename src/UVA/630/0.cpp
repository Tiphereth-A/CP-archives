#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    string a, b;
    map<string, vector<string>> m;
    int n;
    scanf("%d", &n);
    while (n--) {
      cin >> a;
      b = a;
      transform(b.begin(), b.end(), b.begin(), ::toupper);
      sort(b.begin(), b.end());
      m[b].push_back(a);
    }
    for (; cin >> a, a != "END";) {
      b = a;
      transform(b.begin(), b.end(), b.begin(), ::toupper);
      sort(b.begin(), b.end());
      int len = m[b].size();
      cout << "Anagrams for: " << a << endl;
      if (!len) cout << "No anagrams for: " << a << endl;
      else
        for (int i = 0, num = 0; i < len; i++)
          cout << "  " << ++num << ") " << m[b][i] << endl;
    }
    if (t) cout << endl;
  }
  return 0;
}
