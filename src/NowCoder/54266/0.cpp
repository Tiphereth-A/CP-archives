#include <bits/stdc++.h>
const double res[] = {0.000000,
                      0.500000,
                      0.625000,
                      0.666667,
                      0.682292,
                      0.688542,
                      0.691146,
                      0.692262,
                      0.692750,
                      0.692967,
                      0.693065,
                      0.693109,
                      0.693130,
                      0.693139,
                      0.693143,
                      0.693145,
                      0.693146,
                      0.693147};
int n, m;
int main() {
  scanf("%d%d", &n, &m);
  if (m < 17) printf("%f", res[m]);
  else printf("0.693147");
  return 0;
}
