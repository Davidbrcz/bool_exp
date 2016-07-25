#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

#include "expr.h"
#include "listener.h"

using namespace gram;
using namespace antlr4;



int main(int , const char **) {
  ANTLRInputStream input("(true or false) and (true or false) or not(not(true))");
  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  gramParser parser(&tokens);
  Ref<tree::ParseTree> tree = parser.topLevel();
  tree::ParseTreeWalker walker;
  Listener l;
  walker.walk(&l,tree);
  auto e = std::move(l.s.top());
  std::cout << *e << "\n";
  return 0;
}
