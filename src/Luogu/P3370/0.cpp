#include <bits/stdc++.h>
typedef unsigned int uint;
#define M 1505
struct trie {
  bool val;
  uint index;
  trie *nxt[16];
  trie() { val = index = 0; }
} *t = new trie();
uint tab[16] = {
  1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
const uint key = 127;
int ans;
void push(uint code) {
  trie **s = &t;
  while (code) {
    short nxt = code & 15;
    if (!(((*s)->index) & tab[nxt])) {
      (*s)->index |= tab[nxt];
      (*s)->nxt[nxt] = new trie();
    }
    s = &((*s)->nxt[nxt]);
    code >>= 3;
  }
  ans += ((*s)->val) ^ 1;
  (*s)->val = true;
}
uint getHash(char str[]) {
  uint len = strlen(str), ans = 0;
  for (int i = 0; i < len; ++i) ans = ans * key + (uint)str[i];
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    char s[M] = "";
    scanf("%s", s);
    push(getHash(s));
  }
  printf("%d", ans);
  return 0;
}
