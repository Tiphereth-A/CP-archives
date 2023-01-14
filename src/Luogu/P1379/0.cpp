#include <bits/stdc++.h>
typedef int State[9];
const int frac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const State _end = {1, 2, 3, 8, 0, 4, 7, 6, 5};
bool exist[400005];
int front = 1, rear = 2;
struct STATE {
  State seq;
  int dist;
  int get_order() {
    int num = 0;
    for (int i = 0; i < 9; ++i) {
      int tmp = 0, cur = seq[i];
      for (int j = i + 1; j < 9; ++j)
        if (cur > seq[j]) ++tmp;
      num += tmp * frac[8 - i];
    }
    return num;
  }
} state_all[1000005], end;
void swap(int &a, int &b) { a ^= b ^= a ^= b; }
int bfs() {
  while (front < rear) {
    State &now = state_all[front].seq;
    if (!memcmp(now, _end, sizeof(_end))) return state_all[front].dist;
    int z;
    for (z = 0; now[z]; ++z);
    int x = z % 3, y = z / 3;
    for (int i = 0; i < 4; ++i) {
      State &next = state_all[rear].seq;
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
      int nz = ny * 3 + nx;
      memcpy(next, now, sizeof(now));
      swap(next[nz], next[z]);
      if (!exist[state_all[rear].get_order()]) {
        exist[state_all[rear].get_order()] = true;
        state_all[rear].dist = state_all[front].dist + 1;
        ++rear;
      }
    }
    ++front;
  }
  return 0;
}
int main() {
  memcpy(end.seq, _end, sizeof(_end));
  for (int i = 0; i < 9; ++i) state_all[1].seq[i] = getchar() - '0';
  printf("%d", bfs());
  return 0;
}
