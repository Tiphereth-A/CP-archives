const int N = 1e4;
struct point {
    double x, y;
};
point cir;
double dist(point a, point b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
point operator+(point a, point b) { return (point){a.x + b.x, a.y + b.y}; }
point operator-(point a, point b) { return (point){a.x - b.x, a.y - b.y}; }
point operator*(double k, point a) { return (point){k * a.x, k * a.y}; }
double cross_product(point a, point b) { return a.x * b.y - a.y * b.x; }
void get_circle(point a, point b, point c) {
    point p1 = a + b, p2 = a + c;
    p1.x /= 2, p1.y /= 2;
    p2.x /= 2, p2.y /= 2;
    point v1, v2;
    v1.x = (a - b).y, v1.y = -(a - b).x;
    v2.x = (a - c).y, v2.y = -(a - c).x;
    cir = p1 + cross_product(p2 - p1, v2) / cross_product(v1, v2) * v1;
}
int n;
double radius(point p[]) {
    double r = 0;
    random_shuffle(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++)
        if (dist(p[i], cir) > r) {
            cir = p[i], r = 0;
            for (int j = 1; j <= i - 1; j++)
                if (dist(p[j], cir) > r) {
                    cir = p[i] + p[j];
                    cir.x /= 2, cir.y /= 2;
                    r = dist(p[i], p[j]) / 2;
                    for (int k = 1; k <= j - 1; k++)
                        if (dist(p[k], cir) > r) {
                            get_circle(p[i], p[j], p[k]);
                            r = dist(cir, p[k]);
                        }
                }
        }
    return r;
}
double xx[N + 10], yy[N + 10], zz[N + 10];
int main() {
    double ans = 1e4;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf%lf", &xx[i], &yy[i], &zz[i]);
    point temp[N + 10];
    for (int i = 1; i <= n; i++) temp[i].x = xx[i], temp[i].y = yy[i];
    ans = min(ans, radius(temp));
    for (int i = 1; i <= n; i++) temp[i].x = xx[i], temp[i].y = zz[i];
    ans = min(ans, radius(temp));
    for (int i = 1; i <= n; i++) temp[i].x = yy[i], temp[i].y = zz[i];
    ans = min(ans, radius(temp));
    printf("%lf", 2 * ans);
    return 0;
}
