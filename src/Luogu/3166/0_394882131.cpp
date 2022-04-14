#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e3 + OFFSET;
bool vis[N];
i64 prime[N], cnt_prime;
i64 sphi[N], sdphi[N], sddphi[N];
void init_prime(int n = N - 1) {
    sphi[1] = sdphi[1] = sddphi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) sphi[prime[++cnt_prime] = i] = i - 1;
        for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            sphi[i * prime[j]] = sphi[i] * prime[j];
            if (i % prime[j] == 0) break;
            sphi[i * prime[j]] -= sphi[i];
        }
    }
    for (int i = 2; i <= n; ++i) sdphi[i] = sdphi[i - 1] + i * sphi[i];
    for (int i = 2; i <= n; ++i) sddphi[i] = sddphi[i - 1] + i * i * sphi[i];
    for (int i = 2; i <= n; ++i) sphi[i] += sphi[i - 1];
}
i64 c3(i64 n) { return n * (n - 1) / 2 * (n - 2) / 3; }
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    init_prime();
    i64 m, n;
    cin >> m >> n;
    if (n > m) swap(n, m);
    i64 ans = c3((m + 1) * (n + 1)) - (n + 1) * c3(m + 1) - (m + 1) * c3(n + 1);
    for (i64 l = 2, r; l <= n; l = r + 1) {
        r = min(m / (m / l), n / (n / l));
        ans -= 2 * (sphi[r] - sphi[l - 1]) * (n / l) * (m / l) * (n + 1) * (m + 1);
        ans += (sdphi[r] - sdphi[l - 1]) * (n / l) * (m / l) * ((n / l) + 1) * (m + 1);
        ans += (sdphi[r] - sdphi[l - 1]) * (n / l) * (m / l) * ((m / l) + 1) * (n + 1);
        ans -= (sddphi[r] - sddphi[l - 1]) * (n / l) * (m / l) * ((n / l) + 1) / 2 * ((m / l) + 1);
    }
    cout << ans;
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}