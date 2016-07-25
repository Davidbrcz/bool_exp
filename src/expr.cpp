#include "expr.h"
#include <sstream>
#include <iostream>

Expr::~Expr() {}

Not::Not(ref_t<Expr> ee) : e(std::move(ee)) {}

BoolLit::BoolLit(bool bb) : b(bb) {}

And::And(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {}

Or::Or(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {}

std::string Or::toString() const {
  std::cout << "or"  << "\n";
  return std::string{"("}+l->toString() + "||" + r->toString()+")";
}
std::string And::toString() const {
  return std::string{"("}+l->toString() + "&&" + r->toString()+")";
}
std::string BoolLit::toString() const{
  std::cout << "lit" << "\n";
  std::ostringstream os;
  os<<b;
  return os.str();
}

std::string Not::toString() const {

  return std::string{"!("}+e->toString()+")";
}

std::ostream& operator<<(std::ostream& o,const Expr& e){
  std::cout << "op<<"  << "\n";
  o<<e.toString();
  return o;
}
