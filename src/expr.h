#ifndef EXPR_H
#define EXPR_H

#include <memory>

template <class T>
using ref_t = std::unique_ptr<T>;

// template <class U,class ...T>
// auto make_ref(T&& ...e){
//   return std::make_unique<U>(std::forward<T>(e)...);
// }

struct Expr{
   virtual ~Expr() = 0;
};

struct Not : Expr{
  ref_t<Expr> e;
  Not(ref_t<Expr> ee);
};

struct BoolLit : Expr{
  bool b;
  BoolLit(bool bb):b(bb){}
};

struct And : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;
  And(ref_t<Expr> ll,ref_t<Expr> rr):l(std::move(ll)),r(std::move(rr)){}
};

struct Or : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;
  Or(ref_t<Expr> ll,ref_t<Expr> rr):l(std::move(ll)),r(std::move(rr)){}
};

#endif /* EXPR_H */
