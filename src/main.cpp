#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

#include "expr.h"

using namespace gram;
using namespace antlr4;



int main(int , const char **) {
  ANTLRInputStream input("true or false");
  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  gramParser parser(&tokens);
  Ref<tree::ParseTree> tree = parser.topLevel();

  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return 0;
}
