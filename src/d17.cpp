



template <class T> optional<AST::ref_t<AST::Expr>> some(T e) {
  return optional<AST::ref_t<AST::Expr>>(e);
}

#define try_downcast(name, T, expr)                                            \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)))

#define try_downcastCond(name, T, expr, cond)                                  \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)) && (cond))

// #define try_downcast2(name, T, expr)                                           \
//   if (auto name = dynamic_cast<T const *>(&(expr)); static_cast<bool>(name))

optional<AST::ref_t<AST::Expr>> PushNot(AST::ref_t<AST::Expr> const &e) {
  using namespace AST;
  try_downcast(notE, AST::Not, e) {
    try_downcast(subOr, AST::Or, notE->e) {
      auto ret = make_shared<And>(make_shared<AST::Not>(subOr->l),
                                  make_shared<AST::Not>(subOr->r));

      return some(ret);
    }
    else try_downcast(subAnd, AST::And, notE->e) {
      return some(make_shared<Or>(make_shared<Not>(subAnd->l),
                                  make_shared<Not>(subAnd->r)));
    }
  }
  // cerr << "failed" << std::endl;
  return boost::none;
}

optional<AST::ref_t<AST::Expr>> simplify(AST::ref_t<AST::Expr> const &e) {
  using namespace AST;

  try_downcast(andE, AST::And, e) {
    try_downcastCond(lit, AST::BoolLit, andE->l, lit->what() == nature::LitF) {
      return some(make_shared<AST::BoolLit>(false));
    }
    else try_downcastCond(lit, AST::BoolLit, andE->r,
                          lit->what() == nature::LitF) {
      return some(make_shared<AST::BoolLit>(false));
    }
  }

  try_downcast(orE, AST::Or, e) {
    try_downcastCond(lit, AST::BoolLit, orE->l, lit->what() == nature::LitT) {
      return some(make_shared<AST::BoolLit>(true));
    }
    else try_downcastCond(lit, AST::BoolLit, orE->r,
                          lit->what() == nature::LitT) {
      return some(make_shared<AST::BoolLit>(true));
    }
  }

  try_downcast(notE, AST::Not, e) {
    try_downcast(lit, AST::BoolLit, notE->e) {
      return some(make_shared<AST::BoolLit>(!lit->b));
    }
  }

  // cerr << "failed" << std::endl;
  return boost::none;
}

int main(int argc, char *argv[]) {
  using namespace AST;

  auto t = make_shared<Not>(make_shared<And>(
      make_shared<Not>(make_shared<BoolLit>(true)),
      make_shared<Or>(make_shared<BoolLit>(true),
                      make_shared<Not>(make_shared<BoolLit>(false)))));

  cerr << *t << std::endl;

  using namespace Rewrite;
  cerr << "BEGIN"
       << "\n\n";
  auto strat = outermost_(choice_(&PushNot, &simplify));

  if (auto r = strat(t); r) {
    cerr << **r << std::endl;
  }

  return 0;
}
