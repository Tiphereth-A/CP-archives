#include <algorithm>
#include <cstdio>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>
#define INS(a) std::inserter((a), (a).begin())
#define ALL(a) (a).begin(), (a).end()
typedef std::set<int> S;
std::map<S, int> IDCache;
std::vector<S> SetCache;
int findID(S x) {
  if (IDCache.count(x)) return IDCache[x];
  SetCache.push_back(x);
  return IDCache[x] = SetCache.size() - 1;
}
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    int t;
    std::stack<int> s;
    char op[20];
    scanf("%d", &t);
    while (t--) {
      scanf("%s", op);
      if (*op == 'P') s.push(findID(S()));
      else if (*op == 'D') s.push(s.top());
      else {
        S a = SetCache[s.top()];
        s.pop();
        S b = SetCache[s.top()];
        s.pop();
        S x;
        if (*op == 'U') std::set_union(ALL(a), ALL(b), INS(x));
        else if (*op == 'I') std::set_intersection(ALL(a), ALL(b), INS(x));
        else {
          x = b;
          x.insert(findID(a));
        }
        s.push(findID(x));
      }
      printf("%lu\n", SetCache[s.top()].size());
    }
    IDCache.clear();
    SetCache.clear();
    puts("***");
  }
  return 0;
}
