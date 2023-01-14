#include <cstdio>
#include <cstring>
const int N = 205;
int f[N][N];
char str[N];
int min(int x, int y) {
  int m = (x - y) >> 31;
  return x & m | y & ~m;
}
bool match(char a, char b) {
  return (a == '[' && b == ']') || (a == '(' && b == ')');
}
int dfs(int i, int j) {
  if (i > j) return f[i][j] = 0;
  if (i == j) return f[i][j] = 1;
  if (f[i][j] != 0x3f3f3f3f) return f[i][j];
  int ans = f[i][j];
  if (match(str[i], str[j])) ans = min(ans, dfs(i + 1, j - 1));
  for (int k = i; k < j; ++k) ans = min(ans, dfs(i, k) + dfs(k + 1, j));
  return f[i][j] = ans;
}
void print(int i, int j) {
  if (i > j) return;
  if (i == j) {
    if (str[i] == '(' || str[i] == ')') printf("()");
    else printf("[]");
    return;
  }
  int _ = f[i][j];
  if (match(str[i], str[j]) && _ == f[i + 1][j - 1]) {
    putchar(str[i]);
    print(i + 1, j - 1);
    putchar(str[j]);
    return;
  }
  for (int k = i; k < j; ++k)
    if (_ == f[i][k] + f[k + 1][j]) {
      print(i, k);
      print(k + 1, j);
      return;
    }
}
int main() {
  while (fgets(str + 1, N - 1, stdin)) {
    int l_min = 0x3f3f3f3f, len = strlen(str + 1);
    if (str[len]) {
      str[len] = '\0';
      --len;
    }
    memset(f, 0x3f, sizeof(f));
    dfs(1, len);
    print(1, len);
    putchar('\n');
  }
}
