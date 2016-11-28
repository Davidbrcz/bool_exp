
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "gramParser.h"


namespace gram {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by gramParser.
 */
class gramVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by gramParser.
   */
    virtual antlrcpp::Any visitTopLevel(gramParser::TopLevelContext *context) = 0;

    virtual antlrcpp::Any visitAndExpr(gramParser::AndExprContext *context) = 0;

    virtual antlrcpp::Any visitFalseLit(gramParser::FalseLitContext *context) = 0;

    virtual antlrcpp::Any visitTrueLit(gramParser::TrueLitContext *context) = 0;

    virtual antlrcpp::Any visitNotExpr(gramParser::NotExprContext *context) = 0;

    virtual antlrcpp::Any visitParenExpr(gramParser::ParenExprContext *context) = 0;

    virtual antlrcpp::Any visitOrExpr(gramParser::OrExprContext *context) = 0;


};

}  // namespace gram
