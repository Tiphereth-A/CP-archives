#include <bits/stdc++.h>
#define MAXN 35
#define g 6.67408e-11
#define t0 0.01
#define fps 100
using namespace std;
struct point {
  double x, y, z;
  point(double x = 0.0, double y = 0.0, double z = 0.0): x(x), y(y), z(z) {}
  void read() { scanf("%lf%lf%lf", &x, &y, &z); }
  void write() { printf("%.12lf %.12lf %.12lf\n", x, y, z); }
} p[MAXN], v[MAXN];
double m[MAXN];
void operator+=(point &a, const point &b) {
  a.x += b.x, a.y += b.y, a.z += b.z;
}
point operator-(const point &a, const point &b) {
  return (point){a.x - b.x, a.y - b.y, a.z - b.z};
}
point operator*(point &a, double b) {
  return (point){a.x * b, a.y * b, a.z * b};
}
double dis(const point &a) { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
int main() {
  int n, t;
  scanf("%d%d", &n, &t);
  for (int i = 0; i < n; i++) {
    p[i].read();
    scanf("%lf", &m[i]);
    v[i].read();
  }
  for (int k = 0; k < t * fps; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        point diff = p[j] - p[i];
        double dist = dis(diff);
        v[i] += diff * (g * m[j] / dist / dist / dist * t0);
      }
    }
    for (int i = 0; i < n; i++) { p[i] += v[i] * t0; }
  }
  for (int i = 0; i < n; i++) p[i].write();
  return 0;
}
