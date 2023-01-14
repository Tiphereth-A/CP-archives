#include <bits/stdc++.h>
using namespace std;
char key[26];
int main() {
  string s1, s2, s3, s4;
  cin >> s1 >> s2 >> s3;
  for (int i = 0; i < s2.length(); i++)
    if (key[s1[i] - 'A'] == 0) key[s1[i] - 'A'] = s2[i];
    else if (key[s1[i] - 'A'] != s2[i]) {
      cout << "Failed";
      return 0;
    }
  for (int i = 0; i < 26; i++)
    if (key[s1[i] - 'A'] == 0) {
      cout << "Failed";
      return 0;
    }
  string s = key;
  for (char i = 'A'; i <= 'Z'; i++)
    if (s.find(i) != s.rfind(i)) {
      cout << "Failed";
      return 0;
    }
  for (int i = 0; i < s3.length(); i++) cout << key[s3[i] - 'A'];
  return 0;
}
