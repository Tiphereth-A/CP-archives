#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int N = 1e6 + 6;
int n;
namespace AC {
int tr[N][26], tot;
int e[N], fail[N];
void insert(const string &s) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
    u = tr[u][s[i] - 'a'];
  }
  e[u]++;
}
queue<int> q;
void build() {
  for (int i = 0; i < 26; i++)
    if (tr[0][i]) q.push(tr[0][i]);
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u][i]) {
        fail[tr[u][i]] = tr[fail[u]][i];
        q.push(tr[u][i]);
      } else tr[u][i] = tr[fail[u]][i];
    }
  }
}
int query(const string &t) {
  int u = 0, res = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u][t[i] - 'a'];
    for (int j = u; j && e[j] != -1; j = fail[j]) { res += e[j], e[j] = -1; }
  }
  return res;
}
}  // namespace AC
string s;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> s, s = " " + s, AC::insert(s);
  cin >> s;
  s = " " + s;
  AC::build();
  cout << AC::query(s);
  return 0;
}
