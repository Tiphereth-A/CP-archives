#include <cctype>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
const int N = 52;
const char q[] = {'C', 'D', 'H', 'S'};
struct Node {
  int suit, rk;
  Node() {}
  Node(const char *str) {
    suit = strchr(q, str[1]) - q;
    switch (str[0]) {
      case 'A': rk = 1; break;
      case 'T': rk = 10; break;
      case 'J': rk = 11; break;
      case 'Q': rk = 12; break;
      case 'K': rk = 13; break;
      default:
        if (isdigit(str[0])) rk = str[0] - '0';
        break;
    }
  }
  bool operator==(const Node &rhs) const {
    return suit == rhs.suit || rk == rhs.rk;
  }
};
char str[10];
int main() {
#define __                                                                     \
  {                                                                            \
    Node now = pile[k].top(), pre = pile[j].top();                             \
    if (now == pre) {                                                          \
      pile[k].pop();                                                           \
      pile[j].push(now);                                                       \
      if (pile[k].empty()) pile.erase(pile.begin() + k, pile.begin() + k + 1); \
      k = j;                                                                   \
      f = true;                                                                \
      break;                                                                   \
    }                                                                          \
  }
#define _s             \
  {                    \
    stack<Node> _;     \
    _.push(Node(str)); \
    pile.push_back(_); \
  }
  while (~scanf("%s", str)) {
    if (str[0] == '#') break;
    vector<stack<Node>> pile;
    _s;
    for (int i = 2; i <= N; ++i) {
      scanf("%s", str);
      _s;
    }
    bool f = 1;
    while (f) {
      f = 0;
      for (int i = 0, j, k = 0; i < pile.size(); ++i, k = i) {
        if ((j = i - 3) >= 0) __;
        if ((j = i - 1) >= 0) __;
      }
    }
    printf("%d pile%sremaining: ", pile.size(), pile.size() == 1 ? " " : "s ");
    for (int i = 0; i < pile.size(); ++i)
      printf("%d%c", pile[i].size(), " \n"[i == pile.size() - 1]);
  }
  return 0;
}
