#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
vector<pii> points;
map<pii, pii> midp;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    _for(i, 1, n, x, y) {
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    for (auto it = points.begin(); it != points.end(); ++it)
        for (auto it2 = points.begin(); it2 != it; ++it2) {
            auto mid = make_pair(it->first + it2->first, it->second + it2->second);
            auto i = it - points.begin(), j = it2 - points.begin();
            if (!midp.count(mid)) {
                midp[mid] = {i, j};
                continue;
            }
            if (midp[mid].first == i || midp[mid].first == j || midp[mid].second == i || midp[mid].second == j) continue;
            cout << "YES\n"
                 << i + 1 << ' ' << j + 1 << ' ' << midp[mid].first + 1 << ' ' << midp[mid].second + 1 << '\n';
            return;
        }
    cout << "NO\n";
    return 0;
}
