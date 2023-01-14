#include <bits/stdc++.h>
const int frac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const int state_begin[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
struct SEQ {
  int seq[9];
  int step, father, state_ID;
  char oper;
  SEQ(int Step = 0, int Father = 0, int Oper = '\0') {
    memcpy(seq, state_begin, sizeof(state_begin));
    step = Step;
    father = Father;
    oper = Oper;
  }
  SEQ operator=(SEQ &a) {
    memcpy(seq, a.seq, sizeof(a.seq));
    oper = a.oper;
    step = a.step;
    return *this;
  }
  bool operator==(SEQ &a) { return this->get_state() == a.get_state(); }
  int get_state() {
    if (state_ID != 0) return state_ID;
    for (int i = 1; i <= 8; ++i) {
      int tmp = 0;
      for (int j = i + 1; j <= 8; ++j)
        if (seq[i] > seq[j]) ++tmp;
      state_ID += tmp * frac[8 - i];
    }
    return state_ID;
  }
  void operA(const SEQ &a) {
    seq[1] = a.seq[8];
    seq[2] = a.seq[7];
    seq[3] = a.seq[6];
    seq[4] = a.seq[5];
    seq[5] = a.seq[4];
    seq[6] = a.seq[3];
    seq[7] = a.seq[2];
    seq[8] = a.seq[1];
    step = a.step + 1;
    oper = 'A';
  }
  void operB(const SEQ &a) {
    seq[1] = a.seq[4];
    seq[2] = a.seq[1];
    seq[3] = a.seq[2];
    seq[4] = a.seq[3];
    seq[5] = a.seq[6];
    seq[6] = a.seq[7];
    seq[7] = a.seq[8];
    seq[8] = a.seq[5];
    step = a.step + 1;
    oper = 'B';
  }
  void operC(const SEQ &a) {
    seq[1] = a.seq[1];
    seq[2] = a.seq[7];
    seq[3] = a.seq[2];
    seq[4] = a.seq[4];
    seq[5] = a.seq[5];
    seq[6] = a.seq[3];
    seq[7] = a.seq[6];
    seq[8] = a.seq[8];
    step = a.step + 1;
    oper = 'C';
  }
  void clr() {
    memset(seq, 0, sizeof(seq));
    step = father = state_ID = 0;
  }
} s[50005], end;
bool state_existed[50005];
int state_cnt = 1;
std::queue<int> q;
char ans[15];
void add(int fatherID, int nextID) { s[nextID].father = fatherID; }
void print(int ID) {
  printf("%d\n", s[ID].step);
  int len = 0;
  for (; s[ID].father; ID = s[ID].father) ans[++len] = s[ID].oper;
  for (int i = len; i; --i) putchar(ans[i]);
}
void insert_state(int now, SEQ &tmp_state) {
  if (!state_existed[tmp_state.get_state()]) {
    state_existed[tmp_state.get_state()] = true;
    s[++state_cnt] = tmp_state;
    add(now, state_cnt);
    q.push(state_cnt);
  }
}
int bfs() {
  q.push(1);
  SEQ tmp_state;
  tmp_state.clr();
  while (1) {
    int now = q.front();
    SEQ &now_state = s[now];
    if (now_state == end) return now;
    q.pop();
    for (int i = 1; i <= 3; ++i) {
      switch (i) {
        case 1: tmp_state.operA(now_state); break;
        case 2: tmp_state.operB(now_state); break;
        case 3: tmp_state.operC(now_state); break;
      }
      insert_state(now, tmp_state);
      tmp_state.clr();
    }
  }
}
int main() {
  for (int i = 1; i <= 8; ++i) scanf("%d", &end.seq[i]);
  state_existed[s[1].get_state()] = true;
  print(bfs());
  return 0;
}
