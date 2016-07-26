#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

#include "expr.h"
#include "listener.h"
#include "rewriter.h"
using namespace gram;
using namespace antlr4;

int main(int , const char **) {
   // ANTLRInputStream input("(true or false) and (false or true) and true or not(not(true))");
    ANTLRInputStream input("not not true");

  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);  
  gramParser parser(&tokens);
  Ref<tree::ParseTree> tree = parser.topLevel();
  tree::ParseTreeWalker walker;
  Listener l;
  walker.walk(&l,tree);
  auto e = std::make_unique<Top>(std::move(l.s.top()));

  std::cout << "ORIGINAL "<<*e << "\n";
  pushNOT r;
  e->visit(r);
  std::cout << "AFTER PUSH NOT "<<*e << "\n";
  std::cout << "============" << "\n";
  simplify s;
  e->visit(s);
  std::cout << "AFTER SIMPLIFY "<<*e << "\n";
  return 0;
}
