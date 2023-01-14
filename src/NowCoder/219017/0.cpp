#include <bits/stdc++.h>
using namespace std;
const int N = 35;
map<string, int> id;
string team_name[N];
struct Stat {
  int id, points, wins, losses, draws, goals_scored, goals_allowed;
  bool operator<(const Stat &rhs) const {
    if (points != rhs.points) return points > rhs.points;
    if (goals_scored - goals_allowed != rhs.goals_scored - rhs.goals_allowed)
      return goals_scored - goals_allowed >
             rhs.goals_scored - rhs.goals_allowed;
    if (goals_scored != rhs.goals_scored)
      return goals_scored > rhs.goals_scored;
    return team_name[id] < team_name[rhs.id];
  }
} team_stat[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    memset(team_stat, 0, sizeof(team_stat));
    int team, cont;
    cin >> team >> cont;
    for (int j = 1; j <= team; ++j) {
      string _;
      cin >> _;
      id[team_name[j] = _] = j;
      team_stat[j].id = j;
    }
    while (cont--) {
      string a, b;
      int ga, gb;
      cin >> a >> ga >> b >> gb;
      int id_a = id[a], id_b = id[b];
      team_stat[id_a].goals_scored += ga;
      team_stat[id_b].goals_scored += gb;
      team_stat[id_a].goals_allowed += gb;
      team_stat[id_b].goals_allowed += ga;
      if (ga > gb) {
        ++team_stat[id_a].wins;
        ++team_stat[id_b].losses;
        team_stat[id_a].points += 3;
      } else if (ga < gb) {
        ++team_stat[id_b].wins;
        ++team_stat[id_a].losses;
        team_stat[id_b].points += 3;
      } else {
        ++team_stat[id_a].draws;
        ++team_stat[id_a].points;
        ++team_stat[id_b].draws;
        ++team_stat[id_b].points;
      }
    }
    sort(team_stat + 1, team_stat + team + 1);
    cout << "Group " << i << ":" << endl;
    for (int j = 1; j <= team; ++j) {
      Stat &now = team_stat[j];
      cout << team_name[now.id] << " " << now.points << " " << now.wins << " "
           << now.losses << " " << now.draws << " " << now.goals_scored << " "
           << now.goals_allowed << endl;
    }
    if (i != n) cout << endl;
  }
  return 0;
}
