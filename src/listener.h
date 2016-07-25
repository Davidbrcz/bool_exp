#ifndef LISTENER_H
#define LISTENER_H

#include "gramBaseListener.h"

#include "expr.h"

class Listener : public gram::gramBaseListener {

  std::stack<std::unique_ptr<Expr>> s;
public:
  virtual void exitTopLevel(gram::gramParser::TopLevelContext * /*ctx*/) override;
  virtual void exitAndExpr(gram::gramParser::AndExprContext * /*ctx*/) override;
  virtual void exitFalseLit(gram::gramParser::FalseLitContext * /*ctx*/) override;
  virtual void exitTrueLit(gram::gramParser::TrueLitContext * /*ctx*/) override;
  virtual void exitParenExpr(gram::gramParser::ParenExprContext * /*ctx*/) override;
  virtual void exitOrExpr(gram::gramParser::OrExprContext * /*ctx*/) override;
};

#endif /* LISTENER_H */
