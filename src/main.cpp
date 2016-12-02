#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

#include "expr.h"
#include "listener.h"
#include "rewriter.h"
using namespace gram;
using namespace antlr4;
using namespace std;

template <class T> optional<ref_t<AST::Expr>> some(T e) {
  return optional<ref_t<AST::Expr>>(e);
}

#define try_downcast(name, T, expr)                                            \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)))

#define try_downcastCond(name, T, expr, cond)                                  \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)) && (cond))

// #define try_downcast2(name, T, expr)                                           
//   if (auto name = dynamic_cast<T const *>(&(expr)); static_cast<bool>(name))

optional<ref_t<AST::Expr>> PushNot(ref_t<AST::Expr> const &e) {
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

optional<ref_t<AST::Expr>> simplify(ref_t<AST::Expr> const &e) {
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


void test(std::string str){
  ANTLRInputStream input(str);
  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);  
  gramParser parser(&tokens);
  auto tree = parser.topLevel();
  tree::ParseTreeWalker walker;
  Listener l;
  walker.walk(&l,tree);
  auto e = std::move(l.s.top());

  std::cerr << *e << std::endl;

  using namespace Rewrite;
  cerr << "BEGIN" << std::endl;
  auto strat = Outermost(Choice(&PushNot, &simplify));

  if (auto r = strat(e); r) {
    cerr << "RESULT "<<**r <<"\n"<< std::endl;
  }
  
}

int main(int , const char **) {
  test("(true or false) and (false or true) and true or not(not(true))");
  test("not(true or false)");
  test("not(true and false)");
  return 0;
}
