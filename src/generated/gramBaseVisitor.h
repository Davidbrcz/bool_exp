
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramVisitor.h"


namespace gram {

/**
 * This class provides an empty implementation of gramVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class gramBaseVisitor : public gramVisitor {
public:

  virtual antlrcpp::Any visitTopLevel(gramParser::TopLevelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpr(gramParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFalseLit(gramParser::FalseLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrueLit(gramParser::TrueLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNotExpr(gramParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParenExpr(gramParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrExpr(gramParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace gram
