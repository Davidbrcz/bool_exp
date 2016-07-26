#include "expr.h"
#include <sstream>
#include <iostream>
#include "rewriter.h"

Expr::~Expr() {}

Not::Not(ref_t<Expr> ee) : e(std::move(ee)) {
  e->parent=this;
}

BoolLit::BoolLit(bool bb) : b(bb) {}

And::And(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {
  l->parent=this;
  r->parent=this;
}

Or::Or(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {
  l->parent=this;
  r->parent=this;
}
//================================================================================
std::string Or::toString() const {
  return std::string{"("} + l->toString() + "||" + r->toString() + ")";
}
std::string And::toString() const {
  return std::string{"("} + l->toString() + "&&" + r->toString() + ")";
}
std::string BoolLit::toString() const {
  std::ostringstream os;
  os << b;
  return os.str();
}

std::string Not::toString() const {
  return std::string{"!("} + e->toString() + ")";
}
//================================================================================
void Or::visit(rewriter &r) { r.accept(*this); }
void And::visit(rewriter &r) { r.accept(*this); }
void BoolLit::visit(rewriter &) {
  // Nothing to do
}

void Not::visit(rewriter &r) { r.accept(*this); }
//================================================================================
nature Or::what() const { return nature::Or; }
nature And::what() const { return nature::And; }
nature BoolLit::what() const {
  if (b) {
    return nature::LitT;
  } else {
    return nature::LitF;
  }
}

nature Not::what() const { return nature::Not; }
//================================================================================
std::ostream &operator<<(std::ostream &o, const Expr &e) {
  o << e.toString();
  return o;
}
//================================================================================
void Not::replace(Expr* ,ref_t<Expr> with) {
  with->parent = this;
  e=std::move(with);
}
void BoolLit::replace(Expr* ,ref_t<Expr> with) {
  std::cout << "SHOULD NOT HAPPEN" << "\n";
}
void And::replace(Expr* what,ref_t<Expr> with) {
  with->parent = this;
  if(l.get()==what){
    l=std::move(with);
  }else if(r.get()==what){
    r=std::move(with);
  }else{
    std::cout << "ERROR AND"  << "\n";
  }
}

void Or::replace(Expr* what,ref_t<Expr> with) {
  with->parent = this;
  if(l.get()==what){
    l=std::move(with);
  }else if(r.get()==what){
    r=std::move(with);
  }else{
    std::cout << "ERROR OR" << *what << " by "<< *with   << "\n";
  }
}

Top::Top(ref_t<Expr> ee):e(std::move(ee)){e->parent=this;}
std::string Top::toString() const {return e->toString();}
void Top::visit(rewriter &r) {e->visit(r);}
nature Top::what() const {return nature::Top;}
void Top::replace(Expr* what,ref_t<Expr> with) {
  e=std::move(with);
}

