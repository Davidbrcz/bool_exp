
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramVisitor.h"


namespace gram {

/**
 * This class provides an empty implementation of gramVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 *
 * @param <T> The return type of the visit operation. Use void for operations with no return type.
 */
template <typename T>
class gramBaseVisitor : public tree::AbstractParseTreeVisitor<T>, public gramVisitor<T> {
public:

  virtual T* visitAndExpr(gramParser::AndExprContext *ctx) override {
    return tree::AbstractParseTreeVisitor<T>::visitChildren(ctx);
  }

  virtual T* visitFalseLit(gramParser::FalseLitContext *ctx) override {
    return tree::AbstractParseTreeVisitor<T>::visitChildren(ctx);
  }

  virtual T* visitTrueLit(gramParser::TrueLitContext *ctx) override {
    return tree::AbstractParseTreeVisitor<T>::visitChildren(ctx);
  }

  virtual T* visitParenExpr(gramParser::ParenExprContext *ctx) override {
    return tree::AbstractParseTreeVisitor<T>::visitChildren(ctx);
  }

  virtual T* visitOrExpr(gramParser::OrExprContext *ctx) override {
    return tree::AbstractParseTreeVisitor<T>::visitChildren(ctx);
  }


};

}  // namespace gram
