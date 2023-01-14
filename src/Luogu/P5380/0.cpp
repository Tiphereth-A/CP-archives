#include <bits/stdc++.h>
#include <ostream>
using Tp = std::ptrdiff_t;
using coordinate_type = std::pair<Tp, Tp>;
constexpr coordinate_type operator-(const coordinate_type &lhs,
                                    const coordinate_type &rhs) {
  return {lhs.first - rhs.first, lhs.second - rhs.second};
}
std::ostream &operator<<(std::ostream &os, const coordinate_type &coord) {
  return os << '(' << coord.first << ',' << coord.second << ')';
}
class Command final {
public:
  constexpr explicit Command() = default;
  friend std::istream &operator>>(std::istream &is, Command &cmd) {
    return is >> cmd.from.first >> cmd.from.second >> cmd.to.first >>
           cmd.to.second;
  }
  friend std::ostream &operator<<(std::ostream &os, const Command &command) {
    os << "from: " << command.from << " to: " << command.to;
    return os;
  }
  [[nodiscard]] constexpr const std::pair<Tp, Tp> &origin() const {
    return from;
  }
  [[nodiscard]] constexpr const std::pair<Tp, Tp> &target() const { return to; }

protected:
  coordinate_type from, to;
};
enum Color { UnknownColor, Red, Blue };
[[nodiscard]] std::string getColorName(Color color) {
  switch (color) {
    case Red: return "red";
    case Blue: return "blue";
    default: return "unknown";
  }
}
enum PieceType {
  UnknownPieceType,
  Captain,
  Guard,
  Elephant,
  Horse,
  Car,
  Duck,
  Soldier
};
[[nodiscard]] std::string getPieceTypeName(PieceType pieceType) {
  switch (pieceType) {
    case Captain: return "captain";
    case Guard: return "guard";
    case Elephant: return "elephant";
    case Horse: return "horse";
    case Car: return "car";
    case Duck: return "duck";
    case Soldier: return "soldier";
    default: return "unknown";
  }
}
class PieceStateData {
public:
  constexpr PieceStateData()
    : color(UnknownColor), pieceType(UnknownPieceType), dead(false) {}
  constexpr PieceStateData(Color color, PieceType pieceType)
    : color(color), pieceType(pieceType), dead(false) {}
  friend std::ostream &operator<<(std::ostream &os,
                                  const PieceStateData &data) {
    return os << "color: " << getColorName(data.color)
              << " pieceType: " << getPieceTypeName(data.pieceType)
              << " dead: " << data.dead;
  }
  [[nodiscard]] constexpr Color getColor() const { return color; }
  constexpr void setColor(Color newColor) { color = newColor; }
  [[nodiscard]] constexpr PieceType getPieceType() const { return pieceType; }
  constexpr void setChessType(PieceType newChessType) {
    pieceType = newChessType;
  }
  [[nodiscard]] constexpr bool isDead() const { return dead; }
  constexpr void setDead() { dead = true; }
  constexpr void clean() {
    color = UnknownColor;
    pieceType = UnknownPieceType;
    dead = false;
  }
  [[nodiscard]] constexpr bool isEmpty() const { return color == UnknownColor; }
  [[nodiscard]] std::string str() const {
    return isEmpty() ? "NA" : colorName() + " " + pieceTypeName();
  }

protected:
  Color color;
  PieceType pieceType;
  bool dead;
  [[nodiscard]] std::string colorName() const { return getColorName(color); }
  [[nodiscard]] std::string pieceTypeName() const {
    return getPieceTypeName(pieceType);
  }
};
template <std::size_t BORDER_X, std::size_t BORDER_Y>
class ChessboardBase final {
public:
  [[nodiscard]] constexpr bool isOutOfRange(const coordinate_type &coord) {
    return coord.first < 0 || coord.second < 0 || coord.first >= BORDER_X ||
           coord.second >= BORDER_Y;
  }
  [[nodiscard]] constexpr PieceStateData &status(const coordinate_type &coord) {
    return status_map[coord.first][coord.second];
  }
  [[nodiscard]] constexpr const PieceStateData &
  status(const coordinate_type &coord) const {
    return status_map[coord.first][coord.second];
  }

protected:
  std::array<std::array<PieceStateData, BORDER_Y>, BORDER_X> status_map;
};
using Chessboard = ChessboardBase<10, 9>;
enum MoveStatus {
  UnknownMoveStatus,
  OK,
  DeadPiece,
  NotFound,
  Occupied,
  OutOfRange,
  Invalid
};
std::string getMoveStatusName(MoveStatus status) {
  switch (status) {
    case OK: return "OK";
    case DeadPiece: return "DeadPiece";
    case NotFound: return "NotFound";
    case Occupied: return "Occupied";
    case OutOfRange: return "OutOfRange";
    case Invalid: return "Invalid";
    default: return "unknown";
  }
}
class PieceBase {
public:
  constexpr PieceBase() = default;
  constexpr PieceBase(Chessboard &chessboard,
                      Color color,
                      PieceType pieceType,
                      const Tp &x,
                      const Tp &y)
    : state(color, pieceType), position(x, y) {
    chessboard.status(this->position) = state;
  }
  friend std::ostream &operator<<(std::ostream &os, const PieceBase &base) {
    return os << base.state << " position: " << base.position;
  }
  [[nodiscard]] constexpr const coordinate_type &getPosition() const {
    return position;
  }
  [[nodiscard]] constexpr const PieceStateData &getState() const {
    return state;
  }
  [[nodiscard]] constexpr PieceStateData &getState() { return state; }
  [[nodiscard]] virtual constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const = 0;
  [[nodiscard]] MoveStatus checkCommand(Chessboard &chessboard,
                                        const Command &cmd) const {
    if (this->state.isDead()) return DeadPiece;
    if (this->position != cmd.origin()) return NotFound;
    if (chessboard.isOutOfRange(cmd.target())) return OutOfRange;
    if (chessboard.status(cmd.target()).getColor() == this->state.getColor())
      return Occupied;
    if (!this->reachable(chessboard, cmd.target())) return Invalid;
    return OK;
  }
  constexpr void moveTo(Chessboard &chessboard, const coordinate_type &coord) {
    chessboard.status(coord) = chessboard.status(this->position);
    chessboard.status(this->position).clean();
    this->position = coord;
  }

protected:
  PieceStateData state;
  coordinate_type position;
};
class PieceCaptain final: public PieceBase {
public:
  PieceCaptain() = default;
  constexpr PieceCaptain(Chessboard &chessboard,
                         Color color,
                         const Tp &x,
                         const Tp &y)
    : PieceBase(chessboard, color, Captain, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    return (diff_y == 0 && (diff_x == 1 || diff_x == -1)) ||
           (diff_x == 0 && (diff_y == 1 || diff_y == -1));
  }
};
class PieceGuard final: public PieceBase {
public:
  PieceGuard() = default;
  constexpr PieceGuard(Chessboard &chessboard,
                       Color color,
                       const Tp &x,
                       const Tp &y)
    : PieceBase(chessboard, color, Guard, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    return (diff_y == 1 || diff_y == -1) && (diff_x == 1 || diff_x == -1);
  }
};
class PieceElephant final: public PieceBase {
public:
  PieceElephant() = default;
  constexpr PieceElephant(Chessboard &chessboard,
                          Color color,
                          const Tp &x,
                          const Tp &y)
    : PieceBase(chessboard, color, Elephant, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    if (!((diff_y == 2 || diff_y == -2) && (diff_x == 2 || diff_x == -2)))
      return false;
    return chessboard
      .status(
        {this->position.first + diff_x / 2, this->position.second + diff_y / 2})
      .isEmpty();
  }
};
class PieceHorse final: public PieceBase {
public:
  PieceHorse() = default;
  constexpr PieceHorse(Chessboard &chessboard,
                       Color color,
                       const Tp &x,
                       const Tp &y)
    : PieceBase(chessboard, color, Horse, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    if (!(((diff_y == 2 || diff_y == -2) && (diff_x == 1 || diff_x == -1)) ||
          ((diff_x == 2 || diff_x == -2) && (diff_y == 1 || diff_y == -1))))
      return false;
    if (diff_x == 1 || diff_x == -1)
      return chessboard
        .status({this->position.first, this->position.second + diff_y / 2})
        .isEmpty();
    else
      return chessboard
        .status({this->position.first + diff_x / 2, this->position.second})
        .isEmpty();
  }
};
class PieceCar final: public PieceBase {
public:
  PieceCar() = default;
  constexpr PieceCar(Chessboard &chessboard,
                     Color color,
                     const Tp &x,
                     const Tp &y)
    : PieceBase(chessboard, color, Car, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    if (diff_x == 0) {
      for (Tp i = 1; i < diff_y; ++i)
        if (!chessboard
               .status({this->position.first, this->position.second + i})
               .isEmpty())
          return false;
      for (Tp i = -1; i > diff_y; --i)
        if (!chessboard
               .status({this->position.first, this->position.second + i})
               .isEmpty())
          return false;
      return true;
    } else if (diff_y == 0) {
      for (Tp i = 1; i < diff_x; ++i)
        if (!chessboard
               .status({this->position.first + i, this->position.second})
               .isEmpty())
          return false;
      for (Tp i = -1; i > diff_x; --i)
        if (!chessboard
               .status({this->position.first + i, this->position.second})
               .isEmpty())
          return false;
      return true;
    }
    return false;
  }
};
class PieceDuck final: public PieceBase {
public:
  PieceDuck() = default;
  constexpr PieceDuck(Chessboard &chessboard,
                      Color color,
                      const Tp &x,
                      const Tp &y)
    : PieceBase(chessboard, color, Duck, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    if (!(((diff_y == 2 || diff_y == -2) && (diff_x == 3 || diff_x == -3)) ||
          ((diff_x == 2 || diff_x == -2) && (diff_y == 3 || diff_y == -3))))
      return false;
    if (diff_x == 3 || diff_x == -3)
      return chessboard
               .status({this->position.first + diff_x / 3 * 2,
                        this->position.second + diff_y / 2})
               .isEmpty() &&
             chessboard
               .status(
                 {this->position.first + diff_x / 3, this->position.second})
               .isEmpty();
    else
      return chessboard
               .status({this->position.first + diff_x / 2,
                        this->position.second + diff_y / 3 * 2})
               .isEmpty() &&
             chessboard
               .status(
                 {this->position.first, this->position.second + diff_y / 3})
               .isEmpty();
  }
};
class PieceSoldier final: public PieceBase {
public:
  PieceSoldier() = default;
  constexpr PieceSoldier(Chessboard &chessboard,
                         Color color,
                         const Tp &x,
                         const Tp &y)
    : PieceBase(chessboard, color, Soldier, x, y) {}
  [[nodiscard]] constexpr bool
  reachable([[maybe_unused]] Chessboard &chessboard,
            const coordinate_type &coord) const override {
    auto &&[diff_x, diff_y] = coord - this->position;
    return (diff_x >= -1 && diff_x <= 1) && (diff_y >= -1 && diff_y <= 1) &&
           !(diff_x == 0 && diff_y == 0);
  }
};
template <std::size_t CountCaptain,
          std::size_t CountGuard,
          std::size_t CountElephant,
          std::size_t CountHorse,
          std::size_t CountCar,
          std::size_t CountDuck,
          std::size_t CountSoldier>
class Player {
  using self = Player<CountCaptain,
                      CountGuard,
                      CountElephant,
                      CountHorse,
                      CountCar,
                      CountDuck,
                      CountSoldier>;

public:
  constexpr Player(Chessboard &chessboard,
                   Color color,
                   std::initializer_list<coordinate_type> coords) {
    auto it = coords.begin();
#define INIT(name)                                               \
  for (auto &now : name##s) {                                    \
    now = Piece##name(chessboard, color, it->first, it->second); \
    ++it;                                                        \
  }
    INIT(Captain)
    INIT(Guard)
    INIT(Elephant)
    INIT(Horse)
    INIT(Car)
    INIT(Duck)
    INIT(Soldier)
#undef INIT
  }
#define GETTER(name)                                                         \
  [[nodiscard]] constexpr const Piece##name &get##name(size_t index) const { \
    return name##s[index];                                                   \
  }
  GETTER(Captain)
  GETTER(Guard)
  GETTER(Elephant)
  GETTER(Horse)
  GETTER(Car)
  GETTER(Duck)
  GETTER(Soldier)
#undef GETTER
  [[nodiscard]] constexpr Color color() const {
    return getCaptain(0).getState().getColor();
  }
  friend std::ostream &operator<<(std::ostream &os, const Player &player) {
#define EXECUTE(name)            \
  os << #name ": " << std::endl; \
  for (auto &&now : player.name##s) os << '\t' << now << std::endl;
    EXECUTE(Captain)
    EXECUTE(Guard)
    EXECUTE(Elephant)
    EXECUTE(Horse)
    EXECUTE(Car)
    EXECUTE(Duck)
    EXECUTE(Soldier)
#undef EXECUTE
    os << "moveStatus: " << player.moveStatus << " from: " << player.from
       << " to: " << player.to;
    return os;
  }
  constexpr self &testCommand(Chessboard &chessboard, const Command &cmd) {
#define EXECUTE(name)                                                \
  for (auto &&now : name##s) {                                       \
    if (now.getState().isDead()) continue;                           \
    moveStatus = now.checkCommand(chessboard, cmd);                  \
    if (moveStatus == NotFound || moveStatus == DeadPiece) continue; \
    return *this;                                                    \
  }
    EXECUTE(Captain)
    EXECUTE(Guard)
    EXECUTE(Elephant)
    EXECUTE(Horse)
    EXECUTE(Car)
    EXECUTE(Duck)
    EXECUTE(Soldier)
#undef EXECUTE
    return *this;
  }
  constexpr self &
  runCommand(Chessboard &chessboard, self &opposite, const Command &cmd) {
#define EXECUTE(name)                                                   \
  for (auto &&now : name##s) {                                          \
    if (now.getState().isDead() || now.getPosition() != cmd.origin())   \
      continue;                                                         \
    from = chessboard.status(cmd.origin());                             \
    to = chessboard.status(cmd.target());                               \
    if (chessboard.status(cmd.target()).getColor() == opposite.color()) \
      opposite.kill(chessboard, cmd.target());                          \
    now.moveTo(chessboard, cmd.target());                               \
    return *this;                                                       \
  }
    EXECUTE(Captain)
    EXECUTE(Guard)
    EXECUTE(Elephant)
    EXECUTE(Horse)
    EXECUTE(Car)
    EXECUTE(Duck)
    EXECUTE(Soldier)
#undef EXECUTE
    return *this;
  }
  [[nodiscard]] constexpr bool reachable(Chessboard &chessboard,
                                         const coordinate_type &coord) const {
#define EXECUTE(name)                                             \
  for (auto &&now : name##s)                                      \
    if (!now.getState().isDead() && now.getPosition() != coord && \
        now.reachable(chessboard, coord))                         \
      return true;
    EXECUTE(Captain)
    EXECUTE(Guard)
    EXECUTE(Elephant)
    EXECUTE(Horse)
    EXECUTE(Car)
    EXECUTE(Duck)
    EXECUTE(Soldier)
#undef EXECUTE
    return false;
  }
  constexpr void kill(Chessboard &chessboard, const coordinate_type &coord) {
    switch (chessboard.status(coord).getPieceType()) {
      case UnknownPieceType: break;
#define EXECUTE(name)                           \
  case name:                                    \
    for (auto &&now : name##s) {                \
      if (now.getPosition() != coord) continue; \
      now.getState().setDead();                 \
      chessboard.status(coord).clean();         \
      break;                                    \
    }                                           \
    break;
        EXECUTE(Captain)
        EXECUTE(Guard)
        EXECUTE(Elephant)
        EXECUTE(Horse)
        EXECUTE(Car)
        EXECUTE(Duck)
        EXECUTE(Soldier)
#undef EXECUTE
    }
  }
  [[nodiscard]] constexpr bool lose() const {
    bool result = true;
    for (const auto &now : Captains) result &= now.getState().isDead();
    return result;
  }
  [[nodiscard]] bool succeed() const {
    return this->moveStatus == MoveStatus::OK;
  }
  [[nodiscard]] std::string str() const { return from.str() + ";" + to.str(); }

protected:
#define VAR(name) std::array<Piece##name, Count##name> name##s
  VAR(Captain);
  VAR(Guard);
  VAR(Elephant);
  VAR(Horse);
  VAR(Car);
  VAR(Duck);
  VAR(Soldier);
#undef VAR
private:
  MoveStatus moveStatus = UnknownMoveStatus;
  PieceStateData from, to;
};
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Chessboard chessboard;
  Player<1, 2, 2, 2, 2, 2, 5> playerRed(chessboard,
                                        Red,
                                        {{0, 4},
                                         {0, 3},
                                         {0, 5},
                                         {0, 2},
                                         {0, 6},
                                         {0, 1},
                                         {0, 7},
                                         {0, 0},
                                         {0, 8},
                                         {2, 0},
                                         {2, 8},
                                         {3, 0},
                                         {3, 2},
                                         {3, 4},
                                         {3, 6},
                                         {3, 8}}),
    playerBlue(chessboard,
               Blue,
               {{9, 4},
                {9, 3},
                {9, 5},
                {9, 2},
                {9, 6},
                {9, 1},
                {9, 7},
                {9, 0},
                {9, 8},
                {7, 0},
                {7, 8},
                {6, 0},
                {6, 2},
                {6, 4},
                {6, 6},
                {6, 8}});
  int q;
  cin >> q;
  Command cmd;
  bool turn = true;
  bool gameOver = false;
  while (q--) {
    cin >> cmd;
    if (gameOver) {
      cout << "Invalid command\n";
      continue;
    }
    auto &&nowPlayer = turn ? playerRed : playerBlue;
    auto &&nextPlayer = turn ? playerBlue : playerRed;
    if (!nowPlayer.testCommand(chessboard, cmd).succeed()) {
      cout << "Invalid command\n";
      continue;
    }
    cout << nowPlayer.runCommand(chessboard, nextPlayer, cmd).str() << ';';
    cout << ((nowPlayer.reachable(chessboard,
                                  nextPlayer.getCaptain(0).getPosition()) ||
              nextPlayer.reachable(chessboard,
                                   nowPlayer.getCaptain(0).getPosition())) ?
               "yes" :
               "no")
         << ';';
    cout << ((nextPlayer.lose() || nowPlayer.lose()) ? gameOver = true,
             "yes" :
                                                       "no")
         << '\n';
    turn ^= true;
  }
  return 0;
}
