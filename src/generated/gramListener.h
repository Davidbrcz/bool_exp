
// Generated from /home/david/code/bool_exp/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramParser.h"


namespace gram {

/**
 * This interface defines an abstract listener for a parse tree produced by gramParser.
 */
class gramListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterTopLevel(gramParser::TopLevelContext *ctx) = 0;
  virtual void exitTopLevel(gramParser::TopLevelContext *ctx) = 0;

  virtual void enterAndExpr(gramParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(gramParser::AndExprContext *ctx) = 0;

  virtual void enterFalseLit(gramParser::FalseLitContext *ctx) = 0;
  virtual void exitFalseLit(gramParser::FalseLitContext *ctx) = 0;

  virtual void enterTrueLit(gramParser::TrueLitContext *ctx) = 0;
  virtual void exitTrueLit(gramParser::TrueLitContext *ctx) = 0;

  virtual void enterNotExpr(gramParser::NotExprContext *ctx) = 0;
  virtual void exitNotExpr(gramParser::NotExprContext *ctx) = 0;

  virtual void enterParenExpr(gramParser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(gramParser::ParenExprContext *ctx) = 0;

  virtual void enterOrExpr(gramParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(gramParser::OrExprContext *ctx) = 0;


};

}  // namespace gram
