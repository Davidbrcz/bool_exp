#include "listener.h"
#include <memory>
#include "expr.h"

void Listener::exitTopLevel(gram::gramParser::TopLevelContext *ctx) {

}
void Listener::exitAndExpr(gram::gramParser::AndExprContext *ctx) {

}

void Listener::exitFalseLit(gram::gramParser::FalseLitContext *ctx) {
  s.push(std::make_unique<BoolLit>(false));
}

void Listener::exitTrueLit(gram::gramParser::TrueLitContext *ctx) {
  s.push(std::make_unique<BoolLit>(true));
}

void Listener::exitOrExpr(gram::gramParser::OrExprContext *ctx) {
  auto&& r = std::move(s.top());
  s.pop();
  
  auto&& l = std::move(s.top());
  s.pop();
  
  s.push(std::make_unique<Or>(std::move(l),std::move(r)));
}
