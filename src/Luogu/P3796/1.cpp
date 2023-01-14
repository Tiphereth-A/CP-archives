#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int N = 156;
namespace AC {
const int SZ = N * 80;
int tot, tr[SZ][26];
int fail[SZ], idx[SZ], val[SZ];
int cnt[N];
void init() {
  memset(fail, 0, sizeof(fail));
  memset(tr, 0, sizeof(tr));
  memset(val, 0, sizeof(val));
  memset(cnt, 0, sizeof(cnt));
  memset(idx, 0, sizeof(idx));
  tot = 0;
}
void insert(const string &s, int id) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
    u = tr[u][s[i] - 'a'];
  }
  idx[u] = id;
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
    for (int j = u; j; j = fail[j]) val[j]++;
  }
  for (int i = 0; i <= tot; i++)
    if (idx[i]) res = max(res, val[i]), cnt[idx[i]] = val[i];
  return res;
}
}  // namespace AC
int n;
string s[N], t;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n) {
    if (n == 0) break;
    AC::init();
    for (int i = 1; i <= n; i++)
      cin >> s[i], s[i] = " " + s[i], AC::insert(s[i], i);
    AC::build();
    cin >> t;
    t = " " + t;
    int x = AC::query(t);
    cout << x << '\n';
    for (int i = 1; i <= n; i++)
      if (AC::cnt[i] == x) cout << (s[i].data() + 1) << '\n';
  }
  return 0;
}
