#include "expr.h"

Expr::~Expr() {}

Not::Not(ref_t<Expr> ee) : e(std::move(ee)) {}

BoolLit::BoolLit(bool bb) : b(bb) {}

And::And(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {}

Or::Or(ref_t<Expr> ll, ref_t<Expr> rr) : l(std::move(ll)), r(std::move(rr)) {}
