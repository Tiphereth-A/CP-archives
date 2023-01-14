#include <bits/stdc++.h>
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define _rep(i, l, r) for (int(i) = (l); (i) < (r); ++(i))
#define _mapping_of_identity(i)
int identity##i = -100000;
switch (pigs[player##i].identity) {
  case 'M': identity##i = 0; break;
  case 'Z': identity##i = 1; break;
  case 'F': identity##i = 2; break;
}
#define _main_action_of_use_f(_now, _from)
{
  int pos = -1;
  if (~(pos = find_card((_now), 'K'))) clr_card((_now), pos);
  else break;
}
using std::cin;
using std::cout;
const bool temp[3][3] = {{0, 0, 1}, {0, 0, 1}, {1, 1, 0}};
int n, m, card_group_head, card_group_rear, MP_pos, ZP_list[15], ZP_cnt,
  FP_list[15], FP_cnt;
char card_group[2005];
bool allys[15], enemys[15], semi_enemys[15], game_fin;
struct Pig {
  char identity, cards[2005];
  int cards_head = 1, cards_rear = 5, health = 4, next_player, last_player;
  bool dead, weapon_wearing;
} pigs[15];
bool hostility(int player1, int player2) {
  _mapping_of_identity(1);
  _mapping_of_identity(2);
  return temp[identity1][identity2];
}
bool game_over() {
  bool tmp = 1;
  _for(i, 1, FP_cnt)
    if (!pigs[FP_list[i]].dead) tmp = 0;
  if (tmp) return 1;
  return pigs[MP_pos].dead;
}
void get_cards(int now_player, int step) {
  Pig *now = &pigs[now_player];
  _for(i, 1, step) {
    now->cards[now->cards_rear] =
      card_group[card_group_head < card_group_rear ? card_group_head :
                                                     (card_group_rear - 1)];
    ++now->cards_rear;
    ++card_group_head;
  }
}
int find_card(int now_player, char card) {
  Pig *now = &pigs[now_player];
  int head_now = now->cards_head, rear_now = now->cards_rear;
  _rep(i, head_now, rear_now) if (now->cards[i] == card) return i;
  return -1;
}
void clr_card(int now_player, int pos) {
  Pig *now = &pigs[now_player];
  now->cards[pos] = '\0';
  if (pos == now->cards_head)
    while (now->cards_head < now->cards_rear &&
           now->cards[now->cards_head] == '\0')
      ++now->cards_head;
}
void dead(int now_player, int from_player) {
  Pig *now = &pigs[now_player], *from = &pigs[from_player];
  if (now->dead) return;
  if (now->health <= 0) {
    int i = -1;
    while (~(i = find_card(now_player, 'P'))) {
      ++now->health;
      clr_card(now_player, i);
      if (now->health > 0) return;
    }
    if (now->health <= 0) {
      now->cards_head = now->cards_rear;
      now->dead = true;
      now->weapon_wearing = false;
      pigs[now->last_player].next_player = now->next_player;
      pigs[now->next_player].last_player = now->last_player;
      if ((game_fin = game_over())) return;
      if (now_player != from_player) {
        if (now->identity == 'F') get_cards(from_player, 3);
        else if (now->identity == 'Z' && from->identity == 'M') {
          from->cards_head = from->cards_rear;
          from->weapon_wearing = false;
        }
      }
    }
  }
}
void print_result() {
  cout << (pigs[MP_pos].dead ? "_for" : "MP") << '\n';
  _for(i, 1, n) {
    if (pigs[i].dead) cout << "DEAD";
    else
      _rep(j, pigs[i].cards_head, pigs[i].cards_rear) if (pigs[i].cards[j]) cout
        << pigs[i].cards[j] << ' ';
    cout << '\n';
  }
}
void use_k(int now_player, int from_player) {
  Pig *now = &pigs[now_player];
  int pos = -1;
  if (~(pos = find_card(now_player, 'D'))) clr_card(now_player, pos);
  else --now->health;
}
bool use_j(int now_player,
           int from_player,
           int target_player,
           bool state = true) {
  int next_player = now_player;
  do {
    if (!pigs[next_player].dead) {
      if (hostility(next_player, target_player) ^ state) {
        int pos = find_card(next_player, 'J');
        if (~pos) {
          clr_card(next_player, pos);
          if (pigs[next_player].identity == 'F') enemys[next_player] = 1;
          else allys[next_player] = 1;
          return use_j(next_player, from_player, target_player, !state);
        }
      }
    }
    next_player = pigs[next_player].next_player;
  } while (next_player != now_player);
  return !state;
}
bool use_f(int now_player, int from_player) {
  Pig *from = &pigs[from_player];
  bool ima_no_pureiyaa = 0;
  if ((allys[now_player] || enemys[now_player]) &&
      use_j(from_player, from_player, now_player))
    return 0;
  if (pigs[now_player].identity == 'Z' && pigs[from_player].identity == 'M') {
    --pigs[now_player].health;
    dead(now_player, from_player);
    return 0;
  }
  while (1) {
    if (ima_no_pureiyaa)
      _main_action_of_use_f(from_player, now_player) else _main_action_of_use_f(
        now_player, from_player) if (from->dead) return 1;
    ima_no_pureiyaa ^= 1;
  }
  if (ima_no_pureiyaa) {
    --from->health;
    dead(from_player, now_player);
  } else {
    --pigs[now_player].health;
    dead(now_player, from_player);
  }
  return from->dead;
}
void use_nw(int from_player, char card) {
  char card_will_be_used = ((card == 'N') ? 'K' : 'D');
  for (int i = pigs[from_player].next_player; i != from_player;
       i = pigs[i].next_player) {
    Pig *now = &pigs[i];
    int pos = -1;
    if ((allys[i] || enemys[i]) && use_j(from_player, from_player, i)) continue;
    if (~(pos = find_card(i, card_will_be_used))) clr_card(i, pos);
    else {
      --now->health;
      if (i == MP_pos) semi_enemys[from_player] = 1;
      dead(i, from_player);
      if (game_fin) return;
    }
  }
}
void action(int now_player) {
  Pig *now = &pigs[now_player];
  int head_now = now->cards_head, target_pos = now->next_player;
  bool used_K = 0;
  while (head_now < now->cards_rear) {
    switch (now->cards[head_now]) {
      case 'Z':
        now->weapon_wearing = true;
        clr_card(now_player, head_now);
        head_now = now->cards_head - 1;
        break;
      case 'P':
        if (now->health < 4) {
          ++now->health;
          clr_card(now_player, head_now);
        }
        break;
      case '\0': break;
      case 'K':
        if (now->weapon_wearing || !used_K) {
          switch (now->identity) {
            case 'M':
              if (enemys[target_pos] ||
                  (!allys[target_pos] && semi_enemys[target_pos])) {
                clr_card(now_player, head_now);
                if (enemys[target_pos]) allys[now_player] = true;
                use_k(target_pos, now_player);
                used_K = true;
                head_now = now->cards_head - 1;
              }
              break;
            case 'Z':
              if (enemys[target_pos]) {
                clr_card(now_player, head_now);
                allys[now_player] = true;
                use_k(target_pos, now_player);
                used_K = true;
                head_now = now->cards_head - 1;
              }
              break;
            case 'F':
              if (allys[target_pos] || pigs[target_pos].identity == 'M') {
                clr_card(now_player, head_now);
                enemys[now_player] = true;
                use_k(target_pos, now_player);
                used_K = true;
                head_now = now->cards_head - 1;
              }
              break;
          }
          dead(target_pos, now_player);
        }
        break;
      case 'F':
        switch (now->identity) {
          case 'M':
            for (int i = target_pos; i != now_player; i = pigs[i].next_player) {
              if ((enemys[i] || (!allys[i] && semi_enemys[i])) &&
                  !pigs[i].dead) {
                clr_card(now_player, head_now);
                if (use_f(i, now_player)) return;
                head_now = now->cards_head - 1;
                break;
              }
            }
            break;
          case 'Z':
            for (int i = target_pos; i != now_player; i = pigs[i].next_player) {
              if (enemys[i] && !pigs[i].dead) {
                clr_card(now_player, head_now);
                allys[now_player] = true;
                if (use_f(i, now_player)) return;
                head_now = now->cards_head - 1;
                break;
              }
            }
            break;
          case 'F':
            clr_card(now_player, head_now);
            enemys[now_player] = true;
            if (use_f(MP_pos, now_player)) return;
            head_now = now->cards_head - 1;
            break;
        }
        break;
      case 'N':
      case 'W':
        use_nw(now_player, now->cards[head_now]);
        clr_card(now_player, head_now);
        head_now = now->cards_head - 1;
        break;
    }
    ++head_now;
    if (game_fin) return;
  }
}
int main() {
  cin >> n >> m;
  card_group_head = 1;
  card_group_rear = m + 1;
  _for(i, 1, n) {
    char tmp[5];
    cin >> tmp >> pigs[i].cards[1] >> pigs[i].cards[2] >> pigs[i].cards[3] >>
      pigs[i].cards[4];
    pigs[i].identity = *tmp;
    pigs[i].next_player = i + 1;
    pigs[i].last_player = i - 1;
    switch (*tmp) {
      case 'M':
        MP_pos = i;
        allys[i] = true;
        break;
      case 'Z': ZP_list[++ZP_cnt] = i; break;
      case 'F': FP_list[++FP_cnt] = i; break;
    }
  }
  _for(i, 1, m) cin >> card_group[i];
  pigs[n].next_player = 1;
  pigs[1].last_player = n;
  if (game_over()) {
    print_result();
    return 0;
  }
  int cnt = 0;
  for (int i = MP_pos; 1; i = pigs[i].next_player) {
    get_cards(i, 2);
    action(i);
    if (game_over()) break;
  }
  print_result();
  return 0;
}
