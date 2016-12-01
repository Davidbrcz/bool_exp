#include "listener.h"
#include <memory>
#include "expr.h"

void Listener::exitTopLevel(gram::gramParser::TopLevelContext *) {

}
void Listener::exitAndExpr(gram::gramParser::AndExprContext *) {
  auto r = std::move(s.top());
  s.pop();
  
  auto l = std::move(s.top());
  s.pop();
  
  s.push(std::make_shared<AST::And>(std::move(l),std::move(r)));
}

void Listener::exitFalseLit(gram::gramParser::FalseLitContext *) {
  s.push(std::make_shared<AST::BoolLit>(false));
}

void Listener::exitTrueLit(gram::gramParser::TrueLitContext *) {
  s.push(std::make_shared<AST::BoolLit>(true));
}

void Listener::exitOrExpr(gram::gramParser::OrExprContext *) {
  auto r = std::move(s.top());
  s.pop();
  
  auto l = std::move(s.top());
  s.pop();
  
  s.push(std::make_shared<AST::Or>(std::move(l),std::move(r)));
}

void Listener::exitNotExpr(gram::gramParser::NotExprContext* ) {
  auto e = std::move(s.top());
  s.pop();
  
  s.push(std::make_shared<AST::Not>(std::move(e)));
}
