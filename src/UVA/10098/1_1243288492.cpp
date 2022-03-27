#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    cin >> kase;
    while (kase--) {
        string str;
        cin >> str;
        sort(str.begin(), str.end());
        cout << str << endl;
        while (next_permutation(str.begin(), str.end())) cout << str << endl;
        cout << endl;
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}