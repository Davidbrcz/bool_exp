#ifndef REWRITER_H
#define REWRITER_H

#include "expr.h"


const bool extern has_changed;
struct rewriter {
  template <class T> void accept(T &expr) {
    if (upon(expr) == ! has_changed) {
      expr.l->visit(*this);
      expr.r->visit(*this);
    }
  }
  void accept(Not &expr) {
    if (upon(expr) == !has_changed) {
      expr.e->visit(*this);
    }
  }

protected:
  virtual bool upon(Not &e) const = 0;
  virtual bool upon(And &e) const = 0;
  virtual bool upon(Or &e) const = 0;
};

struct default_rewriter : rewriter {
protected:
  virtual bool upon(Not &e) const override;
  virtual bool upon(And &e) const override;
  virtual bool upon(Or &e) const override;
};

struct pushNOT : default_rewriter {
protected:
  virtual bool upon(Not &e) const override;
};

struct simplify : default_rewriter {
protected:
  virtual bool upon(Not &e) const override;
  virtual bool upon(And &e) const override;
  virtual bool upon(Or &e) const override;
};

#endif /* REWRITER_H */
