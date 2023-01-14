#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
set<string> p;
set<string>::iterator iter;
string s;
char ch;
int main() {
  while ((ch = getchar()) != EOF) {
    if (!isalpha(ch)) continue;
    while (isalpha(ch)) {
      ch = tolower(ch);
      s += ch;
      ch = getchar();
    }
    p.insert(s);
    s.clear();
  }
  for (iter = p.begin(); iter != p.end(); iter++) cout << *iter << endl;
  return 0;
}
