#include <bits/stdc++.h>
using namespace std;
int f[26][26] = {{0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
                  13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1},
                 {1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,
                  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2},
                 {2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
                  15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3},
                 {3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17,
                  16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4},
                 {4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18,
                  17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5},
                 {5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19,
                  18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6},
                 {6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20,
                  19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7},
                 {7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21,
                  20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8},
                 {8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22,
                  21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9},
                 {9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23,
                  22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
                 {10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24,
                  23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
                 {11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25,
                  24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12},
                 {12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
                  25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13},
                 {13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,
                  0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14},
                 {14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,
                  1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15},
                 {15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,
                  2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17, 16},
                 {16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,
                  3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18, 17},
                 {17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,
                  4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19, 18},
                 {18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,
                  5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20, 19},
                 {19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,  7,
                  6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21, 20},
                 {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,
                  7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22, 21},
                 {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,
                  8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23, 22},
                 {22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
                  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24, 23},
                 {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                  10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25, 24},
                 {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
                  11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  25},
                 {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13,
                  12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0}};
string key, s;
bool mark;
int ch(char c) {
  if ((c >= 'A') && (c <= 'Z')) return c - 'A';
  else return c - 'a';
}
int main() {
  cin >> key >> s;
  int len = key.size();
  for (int i = 0; i < s.size(); ++i) {
    bool mark = false;
    if ((s[i] >= 'A') && (s[i] <= 'Z')) mark = true;
    s[i] = f[ch(s[i])][ch(key[i % len])] + 'a';
    if (mark) s[i] = toupper(s[i]);
    else s[i] = tolower(s[i]);
  }
  cout << s;
  return 0;
}