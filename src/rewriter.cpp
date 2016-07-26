#include "rewriter.h"
#include <iostream>

const bool has_changed = true;

//================================================================================
bool default_rewriter::upon(Not &) const { return !has_changed; }
bool default_rewriter::upon(And &) const { return !has_changed; }
bool default_rewriter::upon(Or &) const { return !has_changed; }
//================================================================================
bool simplify::upon(Not &expr) const {
  if (expr.e->what() == nature::LitT) {
    std::cout << "NOT TRUE found " << expr << "\n";
    expr.replace(std::make_unique<BoolLit>(false));
    return has_changed;
  }

  if (expr.e->what() == nature::LitF) {
    std::cout << "NOT False found " << expr << "\n";
    expr.replace(std::make_unique<BoolLit>(true));
    return has_changed;
  }
  return !has_changed;
}
bool simplify::upon(And &expr) const {
  auto and_lit = [&expr](Expr &e) {
    auto nat_l = e.what();
    if (nat_l == nature::LitT || nat_l == nature::LitF) {
      std::cout << "And LIT found" << expr << "\n";
      return !has_changed;
    }
    return !has_changed;
  };
  bool r = and_lit(*expr.l) || and_lit(*expr.r);
  return r;
}
bool simplify::upon(Or &expr) const {

  auto or_lit = [&expr](Expr &e) {
    auto nat_l = e.what();
    if (nat_l == nature::LitT || nat_l == nature::LitF) {
      std::cout << "Or LIT found " << expr << "\n";
      return !has_changed;
    }
    return !has_changed;
  };
  bool r = or_lit(*expr.l) || or_lit(*expr.r);
  return r;
}
//================================================================================
bool pushNOT::upon(Not &expr) const {
  if (expr.e->what() == nature::And) {
    std::cout << "NOT AND found " << expr << "\n";
    return !has_changed;
  }

  else if (expr.e->what() == nature::Or) {
    std::cout << "NOT OR found" << expr << "\n";
    auto ptr_or = dynamic_cast<Or *>(expr.e.get());
    auto l = std::make_unique<Not>(std::move(ptr_or->l));
    auto r = std::make_unique<Not>(std::move(ptr_or->r));
    expr.replace(std::make_unique<And>(std::move(l), std::move(r)));

    return has_changed;
  }

  else if (expr.e->what() == nature::Not) {
    std::cout << "Double NOT found " << expr << "\n";
    auto ptr_not_in = dynamic_cast<Not *>(expr.e.get());
    expr.replace(std::move(ptr_not_in->e));
    return has_changed;
  }

  return !has_changed;
}
