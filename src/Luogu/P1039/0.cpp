#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
const string day[] = {
  "",
  "Today is Sunday.",
  "Today is Monday.",
  "Today is Tuesday.",
  "Today is Wednesday.",
  "Today is Thursday.",
  "Today is Friday.",
  "Today is Saturday.",
};
int state[105], err;
void f(int who, int f) {
  if (state[who] && state[who] != f) err = 1;
  else state[who] = f;
}
string name[105], say[205];
int w[105];
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m, p;
  cin >> m >> n >> p;
  for_(i, 1, m) cin >> name[i];
  for_(i, 1, p) {
    string _;
    cin >> _;
    _.pop_back();
    for_(j, 1, m)
      if (name[j] == _) {
        w[i] = j;
        break;
      }
    getline(cin, say[i], '\r');
    say[i].erase(say[i].begin());
  }
  int ans = 0;
  for_(today, 1, 7)
    for_(now_ans, 1, m) {
      memset(state, err = 0, sizeof(state));
      for_(i, 1, p, who) {
        who = w[i];
        if (say[i] == "I am guilty.") f(who, now_ans == who ? 1 : -1);
        else if (say[i] == "I am not guilty.") f(who, now_ans != who ? 1 : -1);
        for_(j, 1, 7)
          if (say[i] == day[j]) f(who, j == today ? 1 : -1);
        for_(j, 1, m)
          if (say[i] == name[j] + " is guilty.") f(who, j == now_ans ? 1 : -1);
          else if (say[i] == name[j] + " is not guilty.")
            f(who, j != now_ans ? 1 : -1);
      }
      if (auto cnt = count(state + 1, state + m + 1, -1),
          ppp = count(state + 1, state + m + 1, 0);
          !err && cnt <= n && cnt + ppp >= n) {
        if (ans && ans != now_ans) {
          cout << "Cannot Determine\n";
          return;
        }
        ans = now_ans;
      }
    }
  cout << (ans ? name[ans] : "Impossible") << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
