#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 1e4 + 5;
int n;
std::priority_queue<u64, std::vector<u64>, std::greater<u64>> q;
int main() {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    cin >> n;
    for (int a, i = 1; i <= n; i++) {
        cin >> a;
        q.push(a);
    }
    u64 ans = 0;
    while (q.size() > 1) {
        u64 a = q.top();
        q.pop();
        u64 b = q.top();
        q.pop();
        ans += a + b;
        q.push(a + b);
    }
    cout << ans;
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}