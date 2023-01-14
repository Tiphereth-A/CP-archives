#include <bits/stdc++.h>
#define _teain(i) onlineT |= 1 << i
#define _teaout(i) onlineT &= ~(1 << i)
#define _stuin(i) onlineS |= 1 << i
#define _stuout(i) onlineS &= ~(1 << i)
#define _dead(i) deadS & (1 << i)
#define _killstu deadS |= onlineS
using namespace std;
int n;
string tea[3], stu[5], msg, s1, s2, s3, s4, s5, dead[5];
map<string, int> teaID, stuID;
char onlineT, onlineS, deadS;
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  cin.tie(0);
  cout.tie(0);
  for (int i = 0; i < 3; ++i) {
    cin >> tea[i];
    teaID[tea[i]] = i;
  }
  for (int i = 0; i < 5; ++i) {
    cin >> stu[i];
    stuID[stu[i]] = i;
  }
  cin.ignore(INT_MAX, '\n');
  for (int l = 0; l < n; ++l) {
    getline(cin, msg);
    istringstream iss(msg);
    s1 = s2 = s3 = s4 = s5 = "";
    iss >> s1 >> s2 >> s3 >> s4 >> s5;
    if (s2 == "came!" && s3 == "" && teaID.count(s1)) {
      _teain(teaID[s1]);
      _killstu;
    }
    if (s2 == "left!" && s3 == "" && teaID.count(s1)) { _teaout(teaID[s1]); }
    if (s2 == "started" && s3 == "playing" && s4 == "games!" && s5 == "" &&
        stuID.count(s1)) {
      _stuin(stuID[s1]);
      if (onlineT) _killstu;
    }
    if (s2 == "stopped" && s3 == "playing" && s4 == "games!" && s5 == "" &&
        stuID.count(s1)) {
      _stuout(stuID[s1]);
    }
    if (deadS == '\037') break;
  }
  int j = 0;
  for (int i = 0; i < 5; ++i)
    if (_dead(i)) dead[j++] = stu[i];
  sort(dead, dead + j);
  for (int i = 0; i < j; ++i) cout << dead[i] << ' ';
  if (j == 5) cout << endl << "How Bad Oiers Are!" << endl;
  else if (j == 0) cout << "How Good Oiers Are!" << endl;
  return 0;
}
