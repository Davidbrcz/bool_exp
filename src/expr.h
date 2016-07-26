#ifndef EXPR_H
#define EXPR_H

#include <memory>

class rewriter;
template <class T> using ref_t = std::unique_ptr<T>;

enum class nature { Not, LitT,LitF, And, Or };

struct Expr {
  Expr* parent = nullptr;
  
  virtual ~Expr() = 0;
  virtual std::string toString() const = 0;
  virtual void visit(rewriter &r) = 0;
  virtual nature what() const = 0;
  virtual void replace(Expr* what,ref_t<Expr> with) = 0;
};

std::ostream &operator<<(std::ostream &o, const Expr &e);

struct Not : Expr {
  ref_t<Expr> e;

  Not(ref_t<Expr> ee);
  virtual std::string toString() const override;
  virtual void visit(rewriter &r) override;
  virtual nature what() const override;
  virtual void replace(Expr* what,ref_t<Expr> with) override;
};

struct BoolLit : Expr {
  bool b;
  BoolLit(bool bb);
  virtual std::string toString() const override;
  virtual void visit(rewriter &r) override;
  virtual nature what() const override;
  virtual void replace(Expr* what,ref_t<Expr> with) override;
};

struct And : Expr {
  ref_t<Expr> l;
  ref_t<Expr> r;

  And(ref_t<Expr> ll, ref_t<Expr> rr);
  virtual std::string toString() const override;
  virtual void visit(rewriter &r) override;
  virtual nature what() const override;
  virtual void replace(Expr* what,ref_t<Expr> with) override;
};

struct Or : Expr {
  ref_t<Expr> l;
  ref_t<Expr> r;

  Or(ref_t<Expr> ll, ref_t<Expr> rr);
  virtual std::string toString() const override;
  virtual void visit(rewriter &r) override;
  virtual nature what() const override;
  virtual void replace(Expr* what,ref_t<Expr> with) override;
};

#endif /* EXPR_H */
