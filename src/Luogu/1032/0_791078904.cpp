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
typedef std::pair<std::string, int> node;
std::string a, b;
std::pair<std::string, std::string> map[10];
int total_map;
std::queue<node> queue;
std::map<std::string, int> mm;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> a >> b;
    for (total_map = 1; cin >> map[total_map].first >> map[total_map].second; ++total_map) {
        if (total_map > 7)
            break;
    }
    --total_map;
    queue.push(node(a, 0));
    while (!queue.empty()) {
        node now = queue.front();
        queue.pop();
        if (mm.count(now.first))
            continue;
        if (now.first == b) {
            cout << now.second;
            return 0;
        }
        mm[now.first] = 1;
        if (now.second == 10)
            continue;
        for (int i = 1; i <= total_map; ++i) {
            std::string a("");
            std::string d = map[i].first, r = map[i].second;
            int pos = -1;
            while ((pos = now.first.find(d, pos + 1)) != std::string::npos) {
                a = now.first;
                a.replace(pos, d.size(), r);
                queue.push(node(a, now.second + 1));
            }
        }
    }
    cout << "NO ANSWER!";
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}