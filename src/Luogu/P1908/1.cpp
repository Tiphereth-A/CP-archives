#prag
ma GCC optimize(2)
#prag
  ma GCC optimize(3)
#prag
    ma GCC optimize("Ofast")
#prag
      ma GCC optimize("")
#prag
        ma GCC optimize("-fgcse")
#prag
          ma GCC optimize("-fgcse-lm")
#prag
            ma GCC optimize("-fipa-sra")
#prag
              ma GCC optimize("-ftree-pre")
#prag
                ma GCC optimize("-ftree-vrp")
#prag
                  ma GCC optimize("-fpeephole2")
#prag
                    ma GCC optimize("-ffast-math")
#prag
                      ma GCC optimize("-fsched-spec")
#prag
                        ma GCC optimize("unroll-loops")
#prag
                          ma GCC optimize("-falign-jumps")
#prag
                            ma GCC optimize("-falign-loops")
#prag
                              ma GCC optimize("-falign-labels")
#prag
                                ma GCC optimize("-fdevirtualize")
#prag
                                  ma GCC optimize("-fcaller-saves")
#prag
                                    ma GCC optimize("-fcrossjumping")
#prag
                                      ma GCC optimize("-fthread-jumps")
#prag
                                        ma GCC optimize("-funroll-loops")
#prag
                                          ma GCC optimize("-freorder-blocks")
#prag
                                            ma GCC optimize("-fschedule-insns")
#prag
                                              ma GCC optimize("-functions")
#prag
                                                ma GCC
  optimize("-ftree-tail-merge")
#prag
    ma GCC optimize("-fschedule-insns2")
#prag
      ma GCC optimize("-fstrict-aliasing")
#prag
        ma GCC optimize("-falign-functions")
#prag
          ma GCC optimize("-fcse-follow-jumps")
#prag
            ma GCC optimize("-fsched-interblock")
#prag
              ma GCC optimize("-fpartial-inlining")
#prag
                ma GCC optimize("no-stack-protector")
#prag
                  ma GCC optimize("-freorder-functions")
#prag
                    ma GCC optimize("-findirect-inlining")
#prag
                      ma GCC optimize("-fhoist-adjacent-loads")
#prag
                        ma GCC optimize("-frerun-cse-after-loop")
#prag
                          ma GCC optimize("-small-functions")
#prag
                            ma GCC optimize("-f-small-functions")
#prag
                              ma GCC optimize("-ftree-switch-conversion")
#prag
                                ma GCC optimize("-foptimize-sibling-calls")
#prag
                                  ma GCC optimize("-fexpensive-optimizations")
#prag
                                    ma GCC optimize("-functions-called-once")
#prag
                                      ma GCC
  optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
    namespace FastIO {
  char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
  int p, p3 = -1;
  int getc() {
    return p1 == p2 &&
               (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
             EOF :
             *p1++;
  }
  template <typename T>
  void read(T & x) {
    int f = 0;
    x = 0;
    char ch = getc();
    while (!isdigit(ch)) {
      if (ch == '-') f = 1;
      ch = getc();
    }
    while (isdigit(ch)) {
      x = x * 10 + ch - 48;
      ch = getc();
    }
    if (f) x = -x;
  }
  void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
  template <typename T>
  void print(T x) {
    if (p3 > 1 << 20) flush();
    if (x < 0) buf2[++p3] = 45, x = -x;
    do { a[++p] = x % 10 + 48; } while (x /= 10);
    do { buf2[++p3] = a[p]; } while (--p);
  }
}
using FastIO::print;
using FastIO::read;
const int N = 5e5 + 5;
int n, a[N], b[N];
unsigned long long cnt;
void merge_sort(int l = 1, int r = n) {
  if (l == r) return;
  int mid = ((r - l) >> 1) + l;
  merge_sort(l, mid);
  merge_sort(mid + 1, r);
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j]) {
      b[k++] = a[i++];
    } else {
      cnt += mid - i + 1;
      b[k++] = a[j++];
    }
  }
  while (i <= mid) { b[k++] = a[i++]; }
  while (j <= r) { b[k++] = a[j++]; }
  memcpy(a + l, b + l, sizeof(int) * (r - l + 1));
}
int main() {
  read(n);
  for (int i = 1; i <= n; ++i) read(a[i]);
  merge_sort();
  print(cnt);
  FastIO::flush();
  return 0;
}
