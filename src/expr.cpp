#include "expr.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <string>

using std::literals::string_literals::operator""s;

namespace AST {

Expr::Expr(Expr *p, nature nn) : parent(p), n(nn) {}
nature Expr::what() const { return n; };
Expr::~Expr() {}

Not::Not(ref_t<Expr> ee) : Expr{this, nature::Not}, e(ee) {}
std::string Not::toString() const  {
  return "!("s + e->toString() + ")";
}
std::vector<ref_t<Expr>> Not::children() const  { return {e}; }
ref_t<Expr> Not::clone(std::vector<ref_t<Expr>> args) const  {
  return std::make_shared<Not>(args[0]);
}

BoolLit::BoolLit(bool bb)
    : Expr{this, bb ? nature::LitT : nature::LitF}, b(bb) {}

std::string BoolLit::toString() const  {
  std::ostringstream os;
  os << b;
  return os.str();
}
std::vector<ref_t<Expr>> BoolLit::children() const  { return {}; }
ref_t<Expr> BoolLit::clone(std::vector<ref_t<Expr>> args) const  {
  return std::make_shared<BoolLit>(b);
}

And::And(ref_t<Expr> ll, ref_t<Expr> rr)
    : Expr{this, nature::And}, l((ll)), r((rr)) {}

std::string And::toString() const  {
  return std::string{"("} + l->toString() + "&&" + r->toString() + ")";
}
std::vector<ref_t<Expr>> And::children() const  { return {l, r}; }
ref_t<Expr> And::clone(std::vector<ref_t<Expr>> args) const  {
  return std::make_shared<And>(args[0], args[1]);
}

Or::Or(ref_t<Expr> ll, ref_t<Expr> rr)
    : Expr{this, nature::Or}, l((ll)), r((rr)) {}
std::string Or::toString() const  {
  return "("s + l->toString() + "||" + r->toString() + ")";
}
std::vector<ref_t<Expr>> Or::children() const  { return {l, r}; }
ref_t<Expr> Or::clone(std::vector<ref_t<Expr>> args) const  {
  return std::make_shared<Or>(args[0], args[1]);
}

//================================================================================
std::ostream &operator<<(std::ostream &o, const Expr &e) {
  o << e.toString();
  return o;
}
}
