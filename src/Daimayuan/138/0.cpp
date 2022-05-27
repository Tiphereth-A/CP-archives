#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    if (k >= n) {
        cout << "0\n";
        return 0;
    };
    vector<int> c;
    c.reserve(n);
    _for(i, 1, n, x) {
        cin >> x;
        c.push_back(x);
    }
    sort(c.begin(), c.end());
    priority_queue<int> pq;
    _for(i, 1, n - 1)
        if (c[i] - c[i - 1] > 0) pq.push(c[i] - c[i - 1]);
    while (--k && !pq.empty()) pq.pop();
    i64 ans = 0;
    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
    }
    cout << ans;
#ifdef _LOCAL_
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}