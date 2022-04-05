#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
#define _for_graph(head, e, i, now) for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
#define _fin goto FINISHED
u64 p;
struct Mat {
    u128 data[2][2];
    Mat() {}
    template <typename Up>
    Mat(Up a = 0, Up b = 0, Up c = 0, Up d = 0) {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }
    template <typename Up>
    constexpr Mat &operator=(Up &&rhs) noexcept {
        (*this)(0, 0) = forward<Mat>(rhs)(0, 0);
        (*this)(0, 1) = forward<Mat>(rhs)(0, 1);
        (*this)(1, 0) = forward<Mat>(rhs)(1, 0);
        (*this)(1, 1) = forward<Mat>(rhs)(1, 1);
        return *this;
    }
    inline constexpr u128 &operator()(size_t x, size_t y) noexcept { return this->data[x][y]; }
    Mat operator*(Mat &rhs) noexcept {
        return Mat(((*this)(0, 0) * rhs(0, 0) % p + (*this)(0, 1) * rhs(1, 0) % p) % p,
                   ((*this)(0, 0) * rhs(0, 1) % p + (*this)(0, 1) * rhs(1, 1) % p) % p,
                   ((*this)(1, 0) * rhs(0, 0) % p + (*this)(1, 1) * rhs(1, 0) % p) % p,
                   ((*this)(1, 0) * rhs(0, 1) % p + (*this)(1, 1) * rhs(1, 1) % p) % p);
    }
};
inline constexpr uint64_t dec2uint_mod(const char * const num, const uint64_t mod = UINT64_MAX) {
    size_t len = strlen(num);
    u128 ans = 0;
    for (auto pch = num; pch < num + len;) (((ans *= 10) %= mod) += *(pch++) & 0x0F) %= mod;
    return ans;
}
inline u64 period(u64 p) {
    auto g = [](u64 p) -> u64 {
        static const u64 _[6] = {0, 1, 3, 8, 6, 20};
        if (p <= 5) return _[p];
        return (p % 5 == 1 || p % 5 == 4) ? (p - 1) : ((p + 1) * 2);
    };
    auto gcd = [](u64 n, u64 m) {
        while (m ^= n ^= m ^= n %= m)
            ;
        return n;
    };
    u64 res = 1;
    for (u128 i = 2; i * i <= p; ++i)
        if (p % i == 0) {
            p /= i;
            u64 x = g(i), _ = p;
            while (p % i == 0) p /= i;
            x *= _ / p;
            res = res / gcd(res, x) * x;
        }
    if (p > 1) {
        u64 x = g(p);
        res = res / gcd(res, x) * x;
    }
    return res;
}
inline void solve() {
    string s;
    cin >> s >> p;
    if (p < 2) {
        cout << '0';
        return;
    }
    cout << [](Mat a, u64 b) -> u64 {
        Mat res(1, 0, 0, 1);
        for (; b; b >>= 1, a = a * a)
            if (b & 1) res = res * a;
        return (u64)res(0, 1);
    }({1, 1, 1, 0}, dec2uint_mod(s.c_str(), period(p)));
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef MULTI_CASES
    int _t;
    cin >> _t;
    while (_t--)
#endif
        solve();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}