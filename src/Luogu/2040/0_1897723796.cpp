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
typedef int state_t;
const state_t d[9] = {11, 23, 38, 89, 186, 308, 200, 464, 416};
struct node {
    int step;
    state_t state;
};
std::queue<node> q;
bool in_queue[512];
void push_state_in_queue(const node &now) {
    for (int tmp, i = 0; i < 9; ++i) {
        tmp = now.state ^ d[i];
        if (in_queue[tmp])
            continue;
        q.push({now.step + 1, tmp});
        in_queue[tmp] = 1;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    state_t tmp;
    for (int a, i = 0; i < 9; ++i) {
        cin >> a;
        tmp |= a << i;
    }
    q.push({0, tmp});
    in_queue[tmp] = 1;
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.state == 511) {
            cout << now.step;
            return 0;
        }
        push_state_in_queue(now);
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}