#include "rewriter.h"
#include <iostream>

//================================================================================
void default_rewriter::upon(Not &) const {}
void default_rewriter::upon(And &) const {}
void default_rewriter::upon(Or &) const {}
//================================================================================
void simplify::upon(Not &expr) const {
  if (expr.e->what() == nature::LitT) {
    std::cout << "NOT TRUE found " << expr << "\n";
  }

  if (expr.e->what() == nature::LitF) {
    std::cout << "NOT False found " << expr << "\n";
  }
}
void simplify::upon(And &expr) const {
 auto and_lit = [&expr](Expr &e) {
    auto nat_l = e.what();
    if (nat_l == nature::LitT || nat_l == nature::LitF) {
      std::cout << "And LIT found" << expr << "\n";
      return true;
    }
    return false;
  };
  static_cast<void>(and_lit(*expr.l) || and_lit(*expr.r));
}
void simplify::upon(Or &expr) const {

  auto or_lit = [&expr](Expr &e) {
    auto nat_l = e.what();
    if (nat_l == nature::LitT || nat_l == nature::LitF) {
      std::cout << "Or LIT found " << expr << "\n";
      return true;
    }
    return false;
  };
  static_cast<void>(or_lit(*expr.l) || or_lit(*expr.r));
}
//================================================================================
void pushNOT::upon(Not &expr) const {
  if (expr.e->what() == nature::And) {
    std::cout << "NOT AND found " << expr << "\n";
  }

  else if (expr.e->what() == nature::Or) {
    std::cout << "NOT OR found" << expr << "\n";
  }

  else if (expr.e->what() == nature::Not) {
    std::cout << "Double NOT found " << expr << "\n";
  }
}
