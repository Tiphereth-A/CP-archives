#include <cstring>
#include <iostream>
#include <queue>
#define maxn 8000001
using namespace std;
char s[maxn];
int n, cnt, vis[maxn], rev[maxn], indeg[maxn], ans;
struct trie_node {
  int son[27];
  int fail;
  int flag;
  int ans;
  void init() {
    memset(son, 0, sizeof(son));
    fail = flag = 0;
  }
} trie[maxn];
queue<int> q;
void init() {
  for (int i = 0; i <= cnt; i++) trie[i].init();
  for (int i = 1; i <= n; i++) vis[i] = 0;
  cnt = 0;
  ans = 0;
}
void insert(char *s, int num) {
  int u = 0, len = strlen(s);
  for (int i = 0; i < len; i++) {
    int v = s[i] - 'a';
    if (!trie[u].son[v]) trie[u].son[v] = ++cnt;
    u = trie[u].son[v];
  }
  if (!trie[u].flag) trie[u].flag = num;
  rev[num] = trie[u].flag;
  return;
}
void getfail(void) {
  for (int i = 0; i < 26; i++)
    if (trie[0].son[i]) q.push(trie[0].son[i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int Fail = trie[u].fail;
    for (int i = 0; i < 26; i++) {
      int v = trie[u].son[i];
      if (!v) {
        trie[u].son[i] = trie[Fail].son[i];
        continue;
      }
      trie[v].fail = trie[Fail].son[i];
      indeg[trie[Fail].son[i]]++;
      q.push(v);
    }
  }
}
void topu() {
  for (int i = 0; i <= cnt; i++)
    if (!indeg[i]) q.push(i);
  while (!q.empty()) {
    int fr = q.front();
    q.pop();
    vis[trie[fr].flag] = trie[fr].ans;
    int u = trie[fr].fail;
    trie[u].ans += trie[fr].ans;
    if (!(--indeg[u])) q.push(u);
  }
}
void query(char *s) {
  int u = 0, len = strlen(s);
  for (int i = 0; i < len; i++) u = trie[u].son[s[i] - 'a'], trie[u].ans++;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  init();
  for (int i = 1; i <= n; i++) cin >> s, insert(s, i);
  getfail();
  cin >> s;
  query(s);
  topu();
  for (int i = 1; i <= n; i++) cout << vis[rev[i]] << std::endl;
  return 0;
}