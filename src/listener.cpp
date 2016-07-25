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
  
  s.push(std::make_unique<And>(std::move(l),std::move(r)));
}

void Listener::exitFalseLit(gram::gramParser::FalseLitContext *) {
  s.push(std::make_unique<BoolLit>(false));
}

void Listener::exitTrueLit(gram::gramParser::TrueLitContext *) {
  s.push(std::make_unique<BoolLit>(true));
}

void Listener::exitOrExpr(gram::gramParser::OrExprContext *) {
  auto r = std::move(s.top());
  s.pop();
  
  auto l = std::move(s.top());
  s.pop();
  
  s.push(std::make_unique<Or>(std::move(l),std::move(r)));
}

void Listener::exitNotExpr(gram::gramParser::NotExprContext* ) {
  auto e = std::move(s.top());
  s.pop();
  
  s.push(std::make_unique<Not>(std::move(e)));
}
