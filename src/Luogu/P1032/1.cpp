#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::string;
int main() {
  string a, b;
  std::pair<string, string> map[10];
  int tot_map;
  std::queue<std::pair<string, int>> queue;
  std::map<string, int> mm;
  cin >> a >> b;
  for (tot_map = 1; cin >> map[tot_map].first >> map[tot_map].second; ++tot_map)
    if (tot_map > 7) break;
  --tot_map;
  queue.push(std::pair<string, int>(a, 0));
  while (!queue.empty()) {
    auto now = queue.front();
    queue.pop();
    if (mm.count(now.first)) continue;
    if (now.first == b) {
      cout << now.second;
      return 0;
    }
    mm[now.first] = 1;
    if (now.second == 10) continue;
    for (int i = 1; i <= tot_map; ++i) {
      string a(""), d = map[i].first, r = map[i].second;
      int pos = -1;
      while ((pos = now.first.find(d, pos + 1)) != string::npos) {
        a = now.first;
        a.replace(pos, d.size(), r);
        queue.push(std::pair<string, int>(a, now.second + 1));
      }
    }
  }
  cout << "NO ANSWER!";
}
