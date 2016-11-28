#include <iostream>

#include "antlr4-runtime.h"
#include "gramLexer.h"
#include "gramParser.h"

#include "expr.h"
#include "listener.h"
#include "rewriter.h"
using namespace gram;
using namespace antlr4;


void test(std::string str){
  ANTLRInputStream input(str);
  gramLexer lexer(&input);
  CommonTokenStream tokens(&lexer);  
  gramParser parser(&tokens);
  auto tree = parser.topLevel();
  tree::ParseTreeWalker walker;
  Listener l;
  walker.walk(&l,tree);
  auto e = std::make_unique<Top>(std::move(l.s.top()));

  std::cout << "ORIGINAL "<<*e << "\n";
  pushNOT r;
  e->visit(r);
  std::cout << "AFTER PUSH NOT "<<*e << "\n";
  std::cout << "----------" << "\n";
  simplify s;
  e->visit(s);
  std::cout << "AFTER SIMPLIFY "<<*e << "\n";
  std::cout << "=============" << "\n";
}
int main(int , const char **) {
  test("(true or false) and (false or true) and true or not(not(true))");
  test("not(true or false)");
  test("not(true and false)");
  return 0;
}
