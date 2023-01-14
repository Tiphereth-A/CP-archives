#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
map<pair<char, char>, int> Map;
void solve(int t_ = 0) {
  string S;
  cin >> S;
  vector<int> A(S.size());
  int Max = 0, Ans = 0;
  Rep(i, 1, S.size() - 1) {
    A[i] = A[i - 1] + Map[{S[i], S[i - 1]}];
    if (A[i] > Max) Max = A[i], Ans = i;
  }
  cout << S[Ans] << '\n';
}
int main() {
  Map[{'S', 'P'}] = 1;
  Map[{'S', 'R'}] = -1;
  Map[{'S', 'S'}] = 0;
  Map[{'P', 'S'}] = -1;
  Map[{'P', 'R'}] = 1;
  Map[{'P', 'P'}] = 0;
  Map[{'R', 'S'}] = 1;
  Map[{'R', 'R'}] = 0;
  Map[{'R', 'P'}] = -1;
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
