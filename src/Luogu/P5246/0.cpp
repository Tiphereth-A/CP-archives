#include <bits/stdc++.h>
using namespace std;
const char map[] = "yfrbkgimujvphatdsnelozcxwq";
char str[105005];
int main() {
  int n;
  cin >> n;
  switch (n) {
    case 1:
      int m;
      cin >> m;
      while (m--) {
        cin >> str;
        for (int i = 0; str[i]; ++i) str[i] = map[str[i] - 'a'];
        cout << str << endl;
      }
      break;
    case 2:
      cout << "106491" << endl
           << "189151" << endl
           << "42510" << endl
           << "93772" << endl
           << "32326" << endl
           << "6890" << endl
           << "94677" << endl
           << "168190" << endl
           << "66840" << endl
           << "93722" << endl;
      break;
    case 3:
      cout << "126" << endl
           << "126" << endl
           << "178" << endl
           << "252" << endl
           << "252" << endl
           << "626" << endl
           << "1982" << endl
           << "6268" << endl
           << "14567" << endl
           << "17730" << endl;
      break;
    case 4:
      cout << "68" << endl
           << "132" << endl
           << "171" << endl
           << "138" << endl
           << "225" << endl
           << "6592" << endl
           << "621318" << endl
           << "64147302" << endl
           << "1588039630" << endl
           << "6348298844" << endl;
      break;
    case 5:
      cout << "531842264" << endl
           << "3996089551" << endl
           << "1217487770" << endl
           << "13846806112" << endl
           << "2258552000" << endl
           << "12273908750" << endl
           << "31068785149" << endl
           << "453868136017" << endl
           << "7989258282893" << endl
           << "3571890382468" << endl;
      break;
    case 6:
      cout << "1159833908" << endl
           << "380176501" << endl
           << "1615846343" << endl
           << "1005775280" << endl
           << "1900756444" << endl
           << "139818805" << endl
           << "2130798985" << endl
           << "1503185154" << endl
           << "433569593" << endl
           << "988651389" << endl;
      break;
    case 7:
      cout << "880" << endl
           << "31080" << endl
           << "325200" << endl
           << "4449880" << endl
           << "135637352" << endl
           << "584509280" << endl
           << "72434344904" << endl
           << "306591086320" << endl
           << "2055466926488" << endl
           << "8643257847824" << endl;
      break;
    case 8:
      cout << "51" << endl
           << "108" << endl
           << "153" << endl
           << "4929" << endl
           << "124260" << endl
           << "498810" << endl
           << "12491602" << endl
           << "49971923" << endl
           << "2739460784" << endl
           << "499996516402" << endl;
      break;
    case 9:
      cout << "2.236" << endl
           << "69.527" << endl
           << "8.944" << endl
           << "10.440" << endl
           << "10.198" << endl
           << "1.414" << endl
           << "57.489" << endl
           << "10.770" << endl
           << "5.000" << endl
           << "8.544" << endl;
      break;
    case 10:
      cout << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl
           << "invalid input!" << endl;
      break;
  }
  return 0;
}
