#include <iostream>
#include <sstream>
#include <string>
const int N = 1e5 + 5;
int inOrder[N], postOrder[N], n;
int minw, ans;
int Min(int a, int b) { return a < b ? a : b; }
bool read(int *a) {
  std::string s;
  if (!std::getline(std::cin, s)) return false;
  std::stringstream ss(s);
  int x;
  n = 0;
  while (ss >> x) a[n++] = x;
  return n;
}
void solve(int lIn, int rIn, int lPost, int rPost, int rslt) {
  if (lIn > rIn) return;
  int tmp = postOrder[rPost], pos = lIn;
  rslt += tmp;
  if (lIn == rIn) {
    if (rslt < minw || (minw == rslt && tmp < ans)) {
      minw = rslt;
      ans = tmp;
    }
    return;
  }
  while (inOrder[pos] != tmp) ++pos;
  int len = pos - lIn;
  solve(lIn, pos - 1, lPost, lPost + len - 1, rslt);
  solve(pos + 1, rIn, lPost + len, rPost - 1, rslt);
}
int main() {
  std::ios::sync_with_stdio(false);
  while (read(inOrder)) {
    read(postOrder);
    minw = ans = 0x3f3f3f3f;
    solve(0, n - 1, 0, n - 1, 0);
    std::cout << ans << std::endl;
  }
  return 0;
}
