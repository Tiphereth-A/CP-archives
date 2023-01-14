#include <cstdio>
#include <cstring>
#include <map>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double db;
std::map<char, db> ar;
int main() {
  int n;
  scanf("%d", &n);
  ar['C'] = 12.01;
  ar['H'] = 1.008;
  ar['O'] = 16.00;
  ar['N'] = 14.01;
  char s[105];
  while (n--) {
    scanf("%s", s);
    int len = strlen(s), num = 0;
    db ans = 0.0, atom = 0.0;
    _for(i, 0, len - 1) {
      if (isalpha(s[i])) {
        if (atom > 0.0 && !num) ans += atom;
        else ans += atom * num;
        atom = ar[s[i]];
        num = 0;
      } else num = num * 10 + s[i] - '0';
    }
    if (atom > 0.0 && !num) ans += atom;
    else ans += atom * num;
    printf("%.3lf\n", ans);
  }
  return 0;
}
