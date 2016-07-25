#ifndef EXPR_H
#define EXPR_H

#include <memory>

template <class T>
using ref_t = std::unique_ptr<T>;



struct Expr{
  virtual ~Expr() = 0;
  virtual std::string toString() const = 0;
};

std::ostream& operator<<(std::ostream& o,const Expr& e);

struct Not : Expr{
  ref_t<Expr> e;

  Not(ref_t<Expr> ee);
  Not(Not const &) = delete;
  Not(Not&&) = default;

  virtual  std::string toString() const override;
};

struct BoolLit : Expr{
  bool b;
  BoolLit(bool bb);
  virtual  std::string toString() const override;
};

struct And : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;

  And(ref_t<Expr> ll,ref_t<Expr> rr);
  And(And const &) = delete;
  And(And&&) = default;

  virtual std::string toString() const override;
};

struct Or : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;

  Or(ref_t<Expr> ll,ref_t<Expr> rr);
  Or(Or const &) = delete;
  Or(Or&&) = default;

  virtual std::string toString() const override;
};

#endif /* EXPR_H */
