#include <iostream>
#include <string>
using namespace std;
int a, c[5];
string b;
int main() {
  cin >> a >> b;
  for (int i = 0; i < a; i++) c[int(b[i]) - int('0')]++;
  cout << max(max(max(c[1], c[2]), c[3]), c[4]) << " ";
  cout << min(min(min(c[1], c[2]), c[3]), c[4]) << endl;
  return 0;
}
