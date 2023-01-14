#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 5e5 + OFFSET;
const long long MOD = 27409402759;
template <const unsigned long long _P,
          const unsigned long long _MOD,
          const char _start = 'a'>
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
  unsigned long long operator()(std::size_t l, std::size_t r) const {
    return (hash[r] - (__int128)hash[l] * p[r - l] % _MOD + _MOD) % _MOD;
  }
};
bool vis[N];
int prime[N], cnt_prime;
int min_prime[N];
void init_prime(int n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) min_prime[i] = prime[++cnt_prime] = i;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      min_prime[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
void read(char *str) {
  int f = 0;
  char ch = getc(), *now = str;
  while (!isalpha(ch)) ch = getc();
  while (isalpha(ch)) {
    *(now++) = ch;
    ch = getc();
  }
  *(now++) = '\0';
}
void read(int &x) {
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) ch = getc();
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
}
}  // namespace FastIO
using FastIO::read;
int now_primes[N], cnt_now_primes;
char s[N];
int main() {
  init_prime();
  int n, m;
  read(n);
  read(s);
  read(m);
  Hash_substr<29, MOD> h(s);
  _for(i, 1, m) {
    int l, r;
    read(l);
    read(r);
    --l;
    n = r - l;
    if (h(l, r - 1) == h(l + 1, r)) {
      puts("1");
      continue;
    }
    cnt_now_primes = 0;
    while (n > 1) {
      now_primes[++cnt_now_primes] = min_prime[n];
      n /= min_prime[n];
    }
    n = r - l;
    _for(idx_p, 1, cnt_now_primes) {
      int now = n / now_primes[idx_p];
      if (h(l, r - now) == h(l + now, r)) n = now;
    }
    printf("%d\n", n);
  }
  return 0;
}
