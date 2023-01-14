#include <bits/stdc++.h>
namespace fast_io {
namespace type_traits {
template <class Tp>
using is_int = typename std::conditional<(std::is_integral<Tp>::value &&
                                          std::is_signed<Tp>::value) ||
                                           std::is_same<Tp, __int128_t>::value,
                                         std::true_type,
                                         std::false_type>::type;
template <class Tp>
using is_uint =
  typename std::conditional<(std::is_integral<Tp>::value &&
                             std::is_unsigned<Tp>::value) ||
                              std::is_same<Tp, __uint128_t>::value,
                            std::true_type,
                            std::false_type>::type;
template <class Tp>
using make_uint = typename std::conditional<
  std::is_same<Tp, __int128_t>::value,
  __uint128_t,
  typename std::conditional<std::is_signed<Tp>::value,
                            std::make_unsigned<Tp>,
                            std::common_type<Tp>>::type>::type;
}  // namespace type_traits
template <size_t BUFFER_SIZE>
class FastIn {
  using self = FastIn<BUFFER_SIZE>;

protected:
  char buffer_[BUFFER_SIZE], *now_ = buffer_, *end_ = buffer_;
  FILE *file_;

public:
  explicit FastIn(FILE *file = stdin) noexcept: file_(file) {}
  char fetch() noexcept {
    return this->now_ == this->end_ &&
               (this->end_ = (this->now_ = this->buffer_) +
                             fread(this->buffer_, 1, BUFFER_SIZE, this->file_),
                this->now_ == this->end_) ?
             EOF :
             *(this->now_)++;
  }
  char visit() noexcept {
    return this->now_ == this->end_ &&
               (this->end_ = (this->now_ = this->buffer_) +
                             fread(this->buffer_, 1, BUFFER_SIZE, this->file_),
                this->now_ == this->end_) ?
             EOF :
             *(this->now_);
  }
  void set_file(FILE *file) noexcept {
    this->file_ = file;
    now_ = end_ = buffer_;
  }
  template <
    typename Tp,
    typename std::enable_if<type_traits::is_int<Tp>::value>::type * = nullptr>
  self &read(Tp &n) noexcept {
    bool is_neg = false;
    char ch = this->fetch();
    while (!isdigit(ch)) {
      is_neg |= ch == '-';
      ch = this->fetch();
    }
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 0x0f;
      ch = this->fetch();
    }
    if (is_neg) n = -n;
    return *this;
  }
  template <
    typename Tp,
    typename std::enable_if<type_traits::is_uint<Tp>::value>::type * = nullptr>
  self &read(Tp &n) noexcept {
    char ch = this->fetch();
    while (!isdigit(ch)) ch = this->fetch();
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 0x0f;
      ch = this->fetch();
    }
    return *this;
  }
  self &read(char &n) noexcept {
    n = this->fetch();
    return *this;
  }
  self &read(char *n) noexcept {
    char *n_ = n;
    while (!isgraph(*n_ = this->fetch()));
    while (isgraph(*(++n_) = this->fetch()));
    *n_ = '\0';
    return *this;
  }
  self &read(std::string &n) noexcept {
    n.clear();
    char n_;
    while (!isgraph(n_ = this->fetch()));
    n.push_back(n_);
    while (isgraph(n_ = this->fetch())) n.push_back(n_);
    return *this;
  }
  self &getline(char *n) noexcept {
    char *n_ = n;
    while (!isprint(*n_ = this->fetch()));
    while (isprint(*(++n_) = this->fetch()));
    *n_ = '\0';
    return *this;
  }
  self &getline(std::string &n) noexcept {
    char n_;
    while (!isprint(n_ = this->fetch()));
    n.push_back(n_);
    while (isprint(n_ = this->fetch())) n.push_back(n_);
    return *this;
  }
};
template <size_t BUFFER_SIZE, size_t INT_BUFFER_SIZE>
class FastOut {
  using self = FastOut<BUFFER_SIZE, INT_BUFFER_SIZE>;

private:
  char int_buffer_[INT_BUFFER_SIZE], *now_ib_;

protected:
  char buffer_[BUFFER_SIZE], *now_ = buffer_;
  const char * const end_ = buffer_ + BUFFER_SIZE;
  FILE *file_;

public:
  explicit FastOut(FILE *file = stdout) noexcept: file_(file) {}
  ~FastOut() noexcept { this->flush(); }
  void flush() noexcept {
    fwrite(this->buffer_, 1, this->now_ - this->buffer_, this->file_);
    this->now_ = this->buffer_;
  }
  void set_file(FILE *file) noexcept { this->file_ = file; }
  self &linebreak() noexcept {
    this->write('\n');
    return *this;
  }
  self &space() noexcept {
    this->write(' ');
    return *this;
  }
  self &write(const char &n) noexcept {
    if (this->now_ == this->end_) this->flush();
    *(this->now_++) = n;
    return *this;
  }
  self &write(const char *n) noexcept {
    size_t len = strlen(n), l_;
    const char *n_ = n;
    while (this->now_ + len >= this->end_) {
      l_ = this->end_ - this->now_;
      memcpy(this->now_, n_, l_);
      this->now_ += l_;
      n_ += l_;
      len -= l_;
      this->flush();
    }
    memcpy(this->now_, n_, len);
    this->now_ += len;
    return *this;
  }
  template <
    class Tp,
    typename std::enable_if<type_traits::is_int<Tp>::value>::type * = nullptr>
  self &write(Tp n) noexcept {
    if (n < 0) {
      this->write('-');
      n = -n;
    }
    return this->write(
      static_cast<typename type_traits::make_uint<Tp>::type>(n));
  }
  template <
    class Tp,
    typename std::enable_if<type_traits::is_uint<Tp>::value>::type * = nullptr>
  self &write(Tp n) noexcept {
    this->now_ib_ = this->int_buffer_ + INT_BUFFER_SIZE - 1;
    do { *(--(this->now_ib_)) = char(n % 10) | '0'; } while (n /= 10);
    this->write(this->now_ib_);
    return *this;
  }
  self &write(const std::string &str) noexcept {
    this->write(str.c_str());
    return *this;
  }
};
const std::size_t BUFFER_SIZE = 1 << 21;
FastIn<BUFFER_SIZE> fast_in;
FastOut<BUFFER_SIZE, 21> fast_out;
}  // namespace fast_io
using fast_io::fast_in;
using fast_io::fast_out;
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e6 + OFFSET, M = 2e5 + OFFSET, K = 21;
int kmp[N];
auto solve() -> void {
  int n;
  fast_in.read(n);
  string s, t;
  _for(i, 1, n) {
    fast_in.read(t);
    auto len = min(s.size(), t.size());
    auto __ = t.size();
    t.push_back('#');
    t.append(s.end() - len, s.end());
    for (int j = kmp[0] = -1, i = 1; i < t.size(); kmp[i++] = j) {
      while (~j && t[j + 1] != t[i]) j = kmp[j];
      if (t[j + 1] == t[i]) ++j;
    }
    s.append(t.begin() + kmp[t.size() - 1] + 1, t.begin() + __);
  }
  fast_out.write(s);
}
int main() {
  solve();
  return 0;
}
