#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e6 + OFFSET, M = 2e5 + OFFSET, K = 21;
const long long MOD = 344493229;
template <const unsigned long long _P, const unsigned long long _MOD, const char _start = 'a'>
class Hash_substr {
  protected:
    std::vector<unsigned long long> hash, p;

  public:
    Hash_substr(const std::string &_str) {
        hash.push_back(0);
        p.push_back(1);
        for (char ch : _str) {
            hash.push_back((hash.back() * _P % _MOD + ch - _start + 1) % _MOD);
            p.push_back(p.back() * _P % _MOD);
        }
    }
    unsigned long long operator()(std::size_t l, std::size_t r) const { return ((long long)hash[r] - (long long)hash[l] * p[r - l] % _MOD + _MOD) % _MOD; }
};
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int kase;
    cin >> kase;
    string str;
    while (kase--) {
        cin >> str;
        Hash_substr<29, MOD> hashval(str);
        int ans = 1;
        size_t l = 1, pre_l = 0, r = str.size() - 1, pre_r = str.size();
        for (; l < r; ++l, --r) {
            if (hashval(pre_l, l) != hashval(r, pre_r)) continue;
            ans += 2;
            pre_l = l;
            pre_r = r;
        }
        if (str.size() % 2 == 0 && hashval(pre_l, l) == hashval(r, pre_r)) ++ans;
        cout << ans << endl;
    __end_kase:;
    }
FINISHED:
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}