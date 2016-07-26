#ifndef REWRITER_H
#define REWRITER_H

#include "expr.h"

struct rewriter {
  template <class T> void accept(T& expr){
    upon(expr);
    expr.l->visit(*this);
    expr.r->visit(*this);
  }
  void accept(Not& expr){
    upon(expr);
    expr.e->visit(*this);
  }
protected:
  virtual void upon(Not &e) const = 0;
  virtual void upon(And &e) const = 0;
  virtual void upon(Or &e) const = 0;
};

struct default_rewriter : rewriter{
protected:
  virtual void upon(Not &e) const override;
  virtual void upon(And &e) const override;
  virtual void upon(Or &e) const override;
};

struct pushNOT : default_rewriter{
protected:
  virtual void upon(Not &e) const override;
};

struct simplify : default_rewriter{
protected:
  virtual void upon(Not &e) const override;
  virtual void upon(And &e) const override;
  virtual void upon(Or &e) const override;
};

#endif /* REWRITER_H */
