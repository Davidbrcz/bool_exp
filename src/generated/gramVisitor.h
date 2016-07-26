
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramParser.h"


namespace gram {

/**
 * This template class defines an abstract visitor for a parse tree
 * produced by gramParser.
 *
 * @param <T> The return type of the visit operation. Use void for
 * operations with no return type.
 */
template <typename T>
class gramVisitor : public antlr4::tree::ParseTreeVisitor<T> {
public:

  /**
   * Visit parse trees produced by gramParser.
   */
    virtual T* visitTopLevel(gramParser::TopLevelContext *context) = 0;

    virtual T* visitAndExpr(gramParser::AndExprContext *context) = 0;

    virtual T* visitFalseLit(gramParser::FalseLitContext *context) = 0;

    virtual T* visitTrueLit(gramParser::TrueLitContext *context) = 0;

    virtual T* visitNotExpr(gramParser::NotExprContext *context) = 0;

    virtual T* visitParenExpr(gramParser::ParenExprContext *context) = 0;

    virtual T* visitOrExpr(gramParser::OrExprContext *context) = 0;


};

}  // namespace gram
