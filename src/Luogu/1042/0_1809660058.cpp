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
std::string data;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    for (char c; cin >> c, c != 'E';)
        data += c;
    int w = 0, l = 0;
    for (auto c : data) {
        if (c == 'W')
            ++w;
        else
            ++l;
        if ((w > 10 || l > 10) && (w - l > 1 || l - w > 1)) {
            cout << w << ':' << l << endl;
            w = l = 0;
        }
    }
    cout << w << ':' << l << endl
         << endl;
    w = l = 0;
    for (auto c : data) {
        if (c == 'W')
            ++w;
        else
            ++l;
        if ((w > 20 || l > 20) && (w - l > 1 || l - w > 1)) {
            cout << w << ':' << l << endl;
            w = l = 0;
        }
    }
    cout << w << ':' << l << endl;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}