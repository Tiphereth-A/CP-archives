#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
struct node {
    int x, y, step;
    bool operator==(const node& other) const { return x == other.x && y == other.y; }
} start, end;
int n, map[1005][1005];
std::queue<node> queue;
inline bool valid(int x, int y) {
    return x > 0 && y > 0 && x <= n && y <= n && !map[x][y];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%1d", &map[i][j]);
    scanf("%d%d%d%d", &start.x, &start.y, &end.x, &end.y);
    queue.push(start);
    while (!queue.empty()) {
        node now = queue.front();
        queue.pop();
        if (now == end) {
            printf("%d", now.step);
            break;
        }
        for (int i = 0; i < 4; ++i) {
            int xx = now.x + dx[i], yy = now.y + dy[i];
            if (valid(xx, yy)) {
                map[xx][yy] = 1;
                queue.push({xx, yy, now.step + 1});
            }
        }
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}