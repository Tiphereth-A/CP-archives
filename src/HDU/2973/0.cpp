#include <iostream>
using namespace std;
const int M = 1e6 + 5, N = 3 * M + 7;
bool vis[N];
int sum[M];
int main() {
  for (int i = 2; i < N; ++i)
    if (!vis[i])
      for (int j = 2; j * i < N; ++j) vis[j * i] = 1;
  for (int i = 1; i < M; ++i) sum[i] = sum[i - 1] + !vis[3 * i + 7];
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    cout << sum[n] << endl;
  }
}
