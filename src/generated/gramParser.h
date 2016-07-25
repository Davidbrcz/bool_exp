
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;

namespace gram {

template <typename T>
class gramVisitor;

class gramParser : public Parser {
public:
  enum {
    TRUE = 1, FALSE = 2, OR = 3, AND = 4, CLOSE_PAREN = 5, OPEN_PAREN = 6
  };

  enum {
    RuleExpr = 0
  };

  gramParser(TokenStream *input);
  ~gramParser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class ExprContext; 

  class ExprContext : public ParserRuleContext {
  public:
    ExprContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
   
    ExprContext() { }
    void copyFrom(Ref<ExprContext> const& context);

    virtual ssize_t getRuleIndex() const override;

   
  };

  class AndExprContext : public ExprContext {
  public:
    AndExprContext(Ref<ExprContext> const& ctx);

    Ref<gramParser::ExprContext> l;
    Ref<gramParser::ExprContext> r;
    Ref<tree::TerminalNode> AND();
    std::vector<Ref<ExprContext>> expr();
    Ref<ExprContext> expr(int i);
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    template <typename T>
    T* accept(tree::ParseTreeVisitor<T> *visitor) {
      if (dynamic_cast<gramVisitor<T>*>(visitor) != nullptr)
        return ((gramVisitor<T> *)visitor)->visitAndExpr(this);
      else
        return visitor->visitChildren(this);
    }
  };

  class FalseLitContext : public ExprContext {
  public:
    FalseLitContext(Ref<ExprContext> const& ctx);

    Ref<tree::TerminalNode> FALSE();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    template <typename T>
    T* accept(tree::ParseTreeVisitor<T> *visitor) {
      if (dynamic_cast<gramVisitor<T>*>(visitor) != nullptr)
        return ((gramVisitor<T> *)visitor)->visitFalseLit(this);
      else
        return visitor->visitChildren(this);
    }
  };

  class TrueLitContext : public ExprContext {
  public:
    TrueLitContext(Ref<ExprContext> const& ctx);

    Ref<tree::TerminalNode> TRUE();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    template <typename T>
    T* accept(tree::ParseTreeVisitor<T> *visitor) {
      if (dynamic_cast<gramVisitor<T>*>(visitor) != nullptr)
        return ((gramVisitor<T> *)visitor)->visitTrueLit(this);
      else
        return visitor->visitChildren(this);
    }
  };

  class ParenExprContext : public ExprContext {
  public:
    ParenExprContext(Ref<ExprContext> const& ctx);

    Ref<tree::TerminalNode> OPEN_PAREN();
    Ref<ExprContext> expr();
    Ref<tree::TerminalNode> CLOSE_PAREN();
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    template <typename T>
    T* accept(tree::ParseTreeVisitor<T> *visitor) {
      if (dynamic_cast<gramVisitor<T>*>(visitor) != nullptr)
        return ((gramVisitor<T> *)visitor)->visitParenExpr(this);
      else
        return visitor->visitChildren(this);
    }
  };

  class OrExprContext : public ExprContext {
  public:
    OrExprContext(Ref<ExprContext> const& ctx);

    Ref<gramParser::ExprContext> l;
    Ref<gramParser::ExprContext> r;
    Ref<tree::TerminalNode> OR();
    std::vector<Ref<ExprContext>> expr();
    Ref<ExprContext> expr(int i);
    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    template <typename T>
    T* accept(tree::ParseTreeVisitor<T> *visitor) {
      if (dynamic_cast<gramVisitor<T>*>(visitor) != nullptr)
        return ((gramVisitor<T> *)visitor)->visitOrExpr(this);
      else
        return visitor->visitChildren(this);
    }
  };

  Ref<ExprContext> expr();
  Ref<ExprContext> expr(int precedence);

  virtual bool sempred(Ref<RuleContext> const& _localctx, int ruleIndex, int predicateIndex) override;
  bool exprSempred(Ref<ExprContext> const& _localctx, int predicateIndex);

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
