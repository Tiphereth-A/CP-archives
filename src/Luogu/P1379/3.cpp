#include <bits/stdc++.h>
typedef int State[9];
const int frac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880},
          dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const State _end = {1, 2, 3, 8, 0, 4, 7, 6, 5};
bool exist[400005];
struct node {
  State seq;
  int dis, id;
  node(): seq({0}), dis(0), id(0) {}
  int hash() {
    if (id) return id;
    for (int i = 0; i < 9; ++i) {
      int tmp = 0, cur = seq[i];
      for (int j = i + 1; j < 9; ++j)
        if (cur > seq[j]) ++tmp;
      id += tmp * frac[8 - i];
    }
    return id;
  }
} end;
std::queue<node> state_all;
void swap(int &a, int &b) { a ^= b ^= a ^= b; }
int bfs() {
  while (!state_all.empty()) {
    node now_state = state_all.front();
    state_all.pop();
    State &now = now_state.seq;
    if (!memcmp(now, _end, sizeof(_end))) return now_state.dis;
    int z;
    for (z = 0; now[z]; ++z);
    int x = z % 3, y = z / 3;
    for (int i = 0; i < 4; ++i) {
      node next_state;
      State &next = next_state.seq;
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx > 2 || yy < 0 || yy > 2) continue;
      int zz = yy * 3 + xx;
      memcpy(next, now, sizeof(now));
      swap(next[zz], next[z]);
      if (!exist[next_state.hash()]) {
        exist[next_state.hash()] = 1;
        next_state.dis = now_state.dis + 1;
        state_all.push(next_state);
      }
    }
  }
}
int main() {
  memcpy(end.seq, _end, sizeof(_end));
  node tmp;
  for (int i = 0; i < 9; ++i) tmp.seq[i] = getchar() - '0';
  state_all.push(tmp);
  printf("%d", bfs());
  return 0;
}
