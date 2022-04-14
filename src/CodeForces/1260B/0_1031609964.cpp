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
typedef unsigned int u32;
int main() {
    int t;
    cin >> t;
    while (t--) {
        u32 a, b;
        cin >> a >> b;
        cout << (((a + b) % 3 || std::max(a, b) > 2 * std::min(a, b)) ? "NO" : "YES") << endl;
    }
    return 0;
}