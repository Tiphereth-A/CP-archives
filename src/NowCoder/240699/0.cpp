#include <bits/stdc++.h>
using namespace std;
int8_t rk_hash(char rk) {
  if (isdigit(rk)) return rk - '1';
  if (rk == 'T') return 9;
  if (rk == 'J') return 10;
  if (rk == 'Q') return 11;
  if (rk == 'K') return 12;
  if (rk == 'A') return 13;
  exit(__LINE__);
}
struct Card {
  int8_t rank;
  char suit;
  Card(char rank = '1', char suit = 0): rank(rk_hash(rank)), suit(suit) {}
  friend bool operator<(const Card &lhs, const Card &rhs) {
    return lhs.rank < rhs.rank;
  }
  friend bool operator>(const Card &lhs, const Card &rhs) {
    return lhs.rank > rhs.rank;
  }
  friend istream &operator>>(istream &is, Card &card) {
    char ch;
    is >> ch >> card.suit;
    card.rank = rk_hash(ch);
    return is;
  }
};
struct Person {
  array<Card, 5> cards;
  Person(string_view s = "00000"): cards{s[0], s[1], s[2], s[3], s[4]} {}
  Card &operator[](size_t i) { return cards[i]; }
  Card operator[](size_t i) const { return cards[i]; }
  void resort(size_t st = 0, size_t ed = 5) {
    sort(cards.begin() + st, cards.begin() + ed, greater<Card>());
  }
  friend uint32_t hasher(Person p) {
    p.resort();
    return ((((uint32_t)p.cards[0].rank * 14 + p.cards[1].rank) * 14 +
             p.cards[2].rank) *
              14 +
            p.cards[3].rank) *
             14 +
           p.cards[4].rank;
  }
  friend bool operator<(Person &lhs, Person &rhs) {
    return lhs.cards < rhs.cards;
  }
  bool is_same_suit() const {
    return cards[4].suit == cards[3].suit && cards[3].suit == cards[2].suit &&
           cards[2].suit == cards[1].suit && cards[1].suit == cards[0].suit;
  }
  bool is_royal_flush() {
    if (!is_same_suit()) return false;
    if (hasher(*this) != hasher(Person("TJQKA"))) return false;
    for (int i = 0; i < 5; ++i)
      if (cards[i].rank == rk_hash('A')) {
        cards[i].rank = 0;
        break;
      }
    return true;
  }
  bool is_straight_flush() { return is_same_suit() && is_straight(); }
  bool is_four_of_a_kind() {
    if (!is_three_of_a_kind()) return false;
    if (cards[0].rank == cards[3].rank) return true;
    if (cards[0].rank == cards[4].rank) {
      swap(cards[3], cards[4]);
      return true;
    }
    return false;
  }
  bool is_full_house() {
    if (!is_three_of_a_kind()) return false;
    return cards[3].rank == cards[4].rank;
  }
  bool is_flush() {
    resort();
    return is_same_suit();
  }
  bool is_straight() {
    resort();
    static unordered_set<uint32_t> us{hasher(Person("A2345")),
                                      hasher(Person("23456")),
                                      hasher(Person("34567")),
                                      hasher(Person("45678")),
                                      hasher(Person("56789")),
                                      hasher(Person("6789T")),
                                      hasher(Person("789TJ")),
                                      hasher(Person("89TJQ")),
                                      hasher(Person("9TJQK")),
                                      hasher(Person("TJQKA"))};
    if (!us.count(hasher(*this))) return false;
    for (int i = 0; i < 5; ++i)
      if (cards[i].rank == rk_hash('A')) {
        cards[i].rank = 0;
        break;
      }
    return true;
  }
  bool is_three_of_a_kind() {
    if (!is_pair()) return false;
    if (cards[0].rank == cards[2].rank) return true;
    if (cards[0].rank == cards[3].rank) {
      swap(cards[2], cards[3]);
      return true;
    }
    if (cards[0].rank == cards[4].rank) {
      swap(cards[2], cards[4]);
      return true;
    }
    return false;
  }
  bool is_two_pairs() {
    if (!is_pair()) return false;
    if (cards[2].rank == cards[3].rank) return true;
    if (cards[3].rank == cards[4].rank) {
      swap(cards[2], cards[4]);
      return true;
    }
    return false;
  }
  bool is_pair() {
    resort();
    if (cards[0].rank == cards[1].rank) {
      resort(2);
      return true;
    }
    if (cards[1].rank == cards[2].rank) {
      swap(cards[0], cards[2]);
      resort(2);
      return true;
    }
    if (cards[2].rank == cards[3].rank) {
      swap(cards[0], cards[2]);
      swap(cards[1], cards[3]);
      resort(2);
      return true;
    }
    if (cards[3].rank == cards[4].rank) {
      swap(cards[0], cards[3]);
      swap(cards[1], cards[4]);
      resort(2);
      return true;
    }
    return false;
  }
  bool is_highcard() {
    resort();
    return true;
  }
  int get_type() {
    if (is_royal_flush()) return 10;
    if (is_straight_flush()) return 9;
    if (is_four_of_a_kind()) return 8;
    if (is_full_house()) return 7;
    if (is_flush()) return 6;
    if (is_straight()) return 5;
    if (is_three_of_a_kind()) return 4;
    if (is_two_pairs()) return 3;
    if (is_pair()) return 2;
    if (is_highcard()) return 1;
    return 0;
  }
};
Person alice, bob;
Card cards[6];
bool vis[6];
int dfs(int now = 0) {
  if (now == 6) {
    Person a_ = alice, b_ = bob;
    int atp = a_.get_type(), btp = b_.get_type();
    if (atp != btp) return atp < btp ? -1 : 1;
    if (a_ < b_) return -1;
    if (b_ < a_) return 1;
    return 0;
  }
  bool can_draw = 0;
  for (int i = 0; i < 6; ++i) {
    if (vis[i]) continue;
    vis[i] = true;
    ((now % 2) ? bob : alice)[now / 2 + 2] = cards[i];
    int _ = dfs(now + 1);
    vis[i] = false;
    if (_ == -1) return 1;
    can_draw |= _ == 0;
  }
  return can_draw ? 0 : -1;
}
const string ans[3] = {"Bob", "Draw", "Alice"};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t_;
  for (cin >> t_; t_; t_--) {
    cin >> alice[0] >> alice[1];
    cin >> bob[0] >> bob[1];
    for (int i = 0; i < 6; ++i) cin >> cards[i];
    memset(vis, 0, sizeof(vis));
    int res = dfs();
    cout << ans[res + 1] << '\n';
  }
  return 0;
}
