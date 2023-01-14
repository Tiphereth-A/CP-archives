#include <bits/stdc++.h>
using std::cin;
using std::cout;
std::string word, docu;
int main() {
  cin >> word;
  for (auto i = word.begin(); i != word.end(); ++i) *i = tolower(*i);
  word = " " + word + " ";
  std::getline(cin, docu);
  std::getline(cin, docu);
  for (auto i = docu.begin(); i != docu.end(); ++i) *i = tolower(*i);
  docu = " " + docu + " ";
  int pos = docu.find(word);
  if (pos == std::string::npos) cout << -1;
  else {
    int i, j;
    for (i = 0, j = pos + 1; ~j; j = docu.find(word, j + 1), ++i) {}
    cout << i << ' ' << pos;
  }
  return 0;
}
