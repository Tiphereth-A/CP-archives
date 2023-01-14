#include <bits/stdc++.h>
char nlist[305][20];
struct node {
  int son[27] = {0};
  int index = 0;
} trie[100000];
int pt, NP, acnt[305], p_acnt;
void trans(char s[]) {
  for (int i = 0; i < strlen(s); ++i)
    if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return;
}
int fnd(char s[]) {
  int len = strlen(s);
  int p = 0, c;
  for (int i = 0; i < len; ++i) {
    c = s[i] - 'a';
    p = trie[p].son[c];
  }
  return trie[p].index;
}
void ins(char s[]) {
  int len = strlen(s);
  int p = 0, c;
  for (int i = 0; i < len; ++i) {
    c = s[i] - 'a';
    if (trie[p].son[c] == 0) trie[p].son[c] = ++pt;
    p = trie[p].son[c];
  }
  trie[p].index = ++p_acnt;
}
int main() {
  int i, j, money, NG;
  char namec[20];
  int namen;
  scanf("%d", &NP);
  for (i = 0; i < NP; ++i) {
    scanf("%s", nlist[i]);
    strcpy(namec, nlist[i]);
    trans(namec);
    ins(namec);
  }
  for (i = 0; i < NP; ++i) {
    scanf("%s\n%d%d", namec, &money, &NG);
    trans(namec);
    int id = fnd(namec);
    acnt[fnd(namec)] -= money;
    if (NG != 0) acnt[fnd(namec)] += money % NG;
    for (j = 0; j < NG; j++) {
      scanf("%s", namec);
      trans(namec);
      int id = fnd(namec);
      acnt[id] += money / NG;
    }
  }
  for (i = 1; i <= NP; ++i) printf("%s %d\n", nlist[i - 1], acnt[i]);
  return 0;
}
