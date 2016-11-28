
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;

namespace gram {


class gramParser : public Parser {
public:
  enum {
    TRUE = 1, FALSE = 2, OR = 3, AND = 4, NOT = 5, CLOSE_PAREN = 6, OPEN_PAREN = 7, 
    WS = 8
  };

  enum {
    RuleTopLevel = 0, RuleExpr = 1
  };

  gramParser(TokenStream *input);
  ~gramParser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class TopLevelContext;
  class ExprContext; 

  class TopLevelContext : public ParserRuleContext {
  public:
    TopLevelContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    tree::TerminalNode *EOF();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  TopLevelContext* topLevel();

  class ExprContext : public ParserRuleContext {
  public:
    ExprContext(ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() : ParserRuleContext() { }
    void copyFrom(ExprContext *context);
    using ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class AndExprContext : public ExprContext {
  public:
    AndExprContext(ExprContext *ctx);

    gramParser::ExprContext *l = nullptr;
    gramParser::ExprContext *r = nullptr;
    tree::TerminalNode *AND();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class FalseLitContext : public ExprContext {
  public:
    FalseLitContext(ExprContext *ctx);

    tree::TerminalNode *FALSE();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class TrueLitContext : public ExprContext {
  public:
    TrueLitContext(ExprContext *ctx);

    tree::TerminalNode *TRUE();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class NotExprContext : public ExprContext {
  public:
    NotExprContext(ExprContext *ctx);

    tree::TerminalNode *NOT();
    ExprContext *expr();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class ParenExprContext : public ExprContext {
  public:
    ParenExprContext(ExprContext *ctx);

    tree::TerminalNode *OPEN_PAREN();
    ExprContext *expr();
    tree::TerminalNode *CLOSE_PAREN();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  class OrExprContext : public ExprContext {
  public:
    OrExprContext(ExprContext *ctx);

    gramParser::ExprContext *l = nullptr;
    gramParser::ExprContext *r = nullptr;
    tree::TerminalNode *OR();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);

  virtual bool sempred(RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace gram
