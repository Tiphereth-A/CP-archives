#include <cstdio>
#include <map>
std::map<int, int> map;
int main() {
  int op, k, p;
  while (~scanf("%d", &op) && op) {
    if (op == 1) {
      scanf("%d%d", &k, &p);
      map[p] = k;
    } else {
      if (map.empty()) {
        puts("0");
        continue;
      }
      if (op == 2) {
        std::map<int, int>::iterator end = map.end();
        --end;
        printf("%d\n", end->second);
        map.erase(end);
      } else if (op == 3) {
        printf("%d\n", map.begin()->second);
        map.erase(map.begin());
      }
    }
  }
}
