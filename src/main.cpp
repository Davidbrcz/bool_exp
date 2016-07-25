#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

template <class T>
using ref_t = std::reference_wrapper<T>;
struct Expr{
   virtual ~Expr() = 0;
};

Expr::~Expr(){}

struct Not : Expr{
  ref_t<Expr> e;
};

struct BoolLit : Expr{
  bool b;
};

struct And : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;
};

struct Or : Expr{
  ref_t<Expr> l;
  ref_t<Expr> r;
};


using namespace gram;
using namespace antlr4;

int main(int , const char **) {
  ANTLRInputStream input("");
  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  gramParser parser(&tokens);
  Ref<tree::ParseTree> tree = parser.expr();

  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return 0;
}
