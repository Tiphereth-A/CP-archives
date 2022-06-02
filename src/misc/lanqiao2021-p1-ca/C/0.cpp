/*
 * @Author: Tifa
 * @LastEditTime: 2021-04-19 19:21:54
 * @Description:
 */
#include <iostream>
#include <set>
#include <tuple>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r) for (auto i = l; i <= r; ++i)
const int pfs[] = {2, 3, 3, 3, 17, 131, 2857, 5882353}, len = sizeof(pfs) / sizeof(pfs[0]);
i64 factors[1 << len];

int main() {
    _for(i, 0, (1 << len) - 1) {
        factors[i] = 1;
        _for(j, 0, len - 1)
            if (i & (1 << j)) factors[i] *= pfs[j];
    }
    set<tuple<i64, i64, i64>> s;
    _for(a, 0, (1 << len) - 1)
        _for(b, 0, (1 << len) - 1)
            _for(c, 0, (1 << len) - 1)
                if (((a | b | c) == (1 << len) - 1) && !((a & b) || (b & c) || (c & a)))
                    s.insert(make_tuple(factors[a], factors[b], factors[c]));
    cout << s.size();
    return 0;
}
