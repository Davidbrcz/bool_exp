
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramListener.h"


namespace gram {

/**
 * This class provides an empty implementation of gramListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class gramBaseListener : public gramListener {
public:

  virtual void enterTopLevel(gramParser::TopLevelContext * /*ctx*/) override { }
  virtual void exitTopLevel(gramParser::TopLevelContext * /*ctx*/) override { }

  virtual void enterAndExpr(gramParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(gramParser::AndExprContext * /*ctx*/) override { }

  virtual void enterFalseLit(gramParser::FalseLitContext * /*ctx*/) override { }
  virtual void exitFalseLit(gramParser::FalseLitContext * /*ctx*/) override { }

  virtual void enterTrueLit(gramParser::TrueLitContext * /*ctx*/) override { }
  virtual void exitTrueLit(gramParser::TrueLitContext * /*ctx*/) override { }

  virtual void enterNotExpr(gramParser::NotExprContext * /*ctx*/) override { }
  virtual void exitNotExpr(gramParser::NotExprContext * /*ctx*/) override { }

  virtual void enterParenExpr(gramParser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(gramParser::ParenExprContext * /*ctx*/) override { }

  virtual void enterOrExpr(gramParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(gramParser::OrExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(tree::ErrorNode * /*node*/) override { }

};

}  // namespace gram
