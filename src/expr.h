#ifndef EXPR_H
#define EXPR_H

#include <boost/optional/optional.hpp>
#include <iosfwd>
#include <memory>
#include <vector>

template <class T> using optional = boost::optional<T>;
template <class T> using ref_t = std::shared_ptr<T>;

namespace AST {

enum class nature { Not, LitT, LitF, And, Or };

struct Expr {
  Expr *parent = nullptr;
  virtual ~Expr() = 0;
  Expr(Expr *p, nature nn);
  virtual std::string toString() const = 0;
  nature what() const;
  const nature n;
  virtual std::vector<ref_t<Expr>> children() const = 0;
  virtual ref_t<Expr> clone(std::vector<ref_t<Expr>> args) const = 0;
};

std::ostream &operator<<(std::ostream &o, const Expr &e);
struct Not : Expr {
  ref_t<Expr> e;
  Not(ref_t<Expr> ee);
  std::string toString() const override;
  std::vector<ref_t<Expr>> children() const override;
  ref_t<Expr> clone(std::vector<ref_t<Expr>> args) const override;
};

struct BoolLit : Expr {
  bool b;
  BoolLit(bool bb);
  std::string toString() const override;
  std::vector<ref_t<Expr>> children() const override;
  ref_t<Expr> clone(std::vector<ref_t<Expr>> args) const override;
};

struct And : Expr {
  ref_t<Expr> l;
  ref_t<Expr> r;
  And(ref_t<Expr> ll, ref_t<Expr> rr);

  std::string toString() const override;
  std::vector<ref_t<Expr>> children() const override;
  ref_t<Expr> clone(std::vector<ref_t<Expr>> args) const override;
};

struct Or : Expr {
  ref_t<Expr> l;
  ref_t<Expr> r;
  Or(ref_t<Expr> ll, ref_t<Expr> rr);
  std::string toString() const override;
  std::vector<ref_t<Expr>> children() const override;
  ref_t<Expr> clone(std::vector<ref_t<Expr>> args) const override;
};
}

#endif /* EXPR_H */
