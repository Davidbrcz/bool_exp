
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3


#include "gramListener.h"
#include "gramVisitor.h"

#include "gramParser.h"


using namespace antlrcpp;
using namespace gram;
using namespace antlr4;

gramParser::gramParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

gramParser::~gramParser() {
  delete _interpreter;
}

std::string gramParser::getGrammarFileName() const {
  return "gram.g4";
}

const std::vector<std::string>& gramParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& gramParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- TopLevelContext ------------------------------------------------------------------

gramParser::TopLevelContext::TopLevelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

gramParser::ExprContext* gramParser::TopLevelContext::expr() {
  return getRuleContext<gramParser::ExprContext>(0);
}

tree::TerminalNode* gramParser::TopLevelContext::EOF() {
  return getToken(gramParser::EOF, 0);
}


size_t gramParser::TopLevelContext::getRuleIndex() const {
  return gramParser::RuleTopLevel;
}

void gramParser::TopLevelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTopLevel(this);
}

void gramParser::TopLevelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTopLevel(this);
}


antlrcpp::Any gramParser::TopLevelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitTopLevel(this);
  else
    return visitor->visitChildren(this);
}

gramParser::TopLevelContext* gramParser::topLevel() {
  TopLevelContext *_localctx = _tracker.createInstance<TopLevelContext>(_ctx, getState());
  enterRule(_localctx, 0, gramParser::RuleTopLevel);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(4);
    expr(0);
    setState(5);
    match(gramParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

gramParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t gramParser::ExprContext::getRuleIndex() const {
  return gramParser::RuleExpr;
}

void gramParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AndExprContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::AndExprContext::AND() {
  return getToken(gramParser::AND, 0);
}

std::vector<gramParser::ExprContext *> gramParser::AndExprContext::expr() {
  return getRuleContexts<gramParser::ExprContext>();
}

gramParser::ExprContext* gramParser::AndExprContext::expr(size_t i) {
  return getRuleContext<gramParser::ExprContext>(i);
}

gramParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::AndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpr(this);
}
void gramParser::AndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpr(this);
}

antlrcpp::Any gramParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseLitContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::FalseLitContext::FALSE() {
  return getToken(gramParser::FALSE, 0);
}

gramParser::FalseLitContext::FalseLitContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::FalseLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFalseLit(this);
}
void gramParser::FalseLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFalseLit(this);
}

antlrcpp::Any gramParser::FalseLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitFalseLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueLitContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::TrueLitContext::TRUE() {
  return getToken(gramParser::TRUE, 0);
}

gramParser::TrueLitContext::TrueLitContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::TrueLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrueLit(this);
}
void gramParser::TrueLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrueLit(this);
}

antlrcpp::Any gramParser::TrueLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitTrueLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::NotExprContext::NOT() {
  return getToken(gramParser::NOT, 0);
}

gramParser::ExprContext* gramParser::NotExprContext::expr() {
  return getRuleContext<gramParser::ExprContext>(0);
}

gramParser::NotExprContext::NotExprContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::NotExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpr(this);
}
void gramParser::NotExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpr(this);
}

antlrcpp::Any gramParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::ParenExprContext::OPEN_PAREN() {
  return getToken(gramParser::OPEN_PAREN, 0);
}

gramParser::ExprContext* gramParser::ParenExprContext::expr() {
  return getRuleContext<gramParser::ExprContext>(0);
}

tree::TerminalNode* gramParser::ParenExprContext::CLOSE_PAREN() {
  return getToken(gramParser::CLOSE_PAREN, 0);
}

gramParser::ParenExprContext::ParenExprContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::ParenExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpr(this);
}
void gramParser::ParenExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpr(this);
}

antlrcpp::Any gramParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

tree::TerminalNode* gramParser::OrExprContext::OR() {
  return getToken(gramParser::OR, 0);
}

std::vector<gramParser::ExprContext *> gramParser::OrExprContext::expr() {
  return getRuleContexts<gramParser::ExprContext>();
}

gramParser::ExprContext* gramParser::OrExprContext::expr(size_t i) {
  return getRuleContext<gramParser::ExprContext>(i);
}

gramParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }

void gramParser::OrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpr(this);
}
void gramParser::OrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<gramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpr(this);
}

antlrcpp::Any gramParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<gramVisitor*>(visitor) != nullptr)
    return ((gramVisitor *)visitor)->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}

gramParser::ExprContext* gramParser::expr() {
   return expr(0);
}

gramParser::ExprContext* gramParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  gramParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  gramParser::ExprContext *previousContext = _localctx;
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, gramParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(16);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case gramParser::TRUE: {
        _localctx = _tracker.createInstance<TrueLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(8);
        match(gramParser::TRUE);
        break;
      }

      case gramParser::FALSE: {
        _localctx = _tracker.createInstance<FalseLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(9);
        match(gramParser::FALSE);
        break;
      }

      case gramParser::NOT: {
        _localctx = _tracker.createInstance<NotExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(10);
        match(gramParser::NOT);
        setState(11);
        expr(4);
        break;
      }

      case gramParser::OPEN_PAREN: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(12);
        match(gramParser::OPEN_PAREN);
        setState(13);
        expr(0);
        setState(14);
        match(gramParser::CLOSE_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(26);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(24);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(18);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(19);
          match(gramParser::AND);
          setState(20);
          dynamic_cast<AndExprContext *>(_localctx)->r = expr(4);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(21);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(22);
          match(gramParser::OR);
          setState(23);
          dynamic_cast<OrExprContext *>(_localctx)->r = expr(3);
          break;
        }

        } 
      }
      setState(28);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool gramParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool gramParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> gramParser::_decisionToDFA;
atn::PredictionContextCache gramParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN gramParser::_atn;
std::vector<uint16_t> gramParser::_serializedATN;

std::vector<std::string> gramParser::_ruleNames = {
  "topLevel", "expr"
};

std::vector<std::string> gramParser::_literalNames = {
  "", "'true'", "'false'", "'or'", "'and'", "'not'", "')'", "'('"
};

std::vector<std::string> gramParser::_symbolicNames = {
  "", "TRUE", "FALSE", "OR", "AND", "NOT", "CLOSE_PAREN", "OPEN_PAREN", 
  "WS"
};

dfa::Vocabulary gramParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> gramParser::_tokenNames;

gramParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0xa, 0x20, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x13, 0xa, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x1b, 0xa, 
    0x3, 0xc, 0x3, 0xe, 0x3, 0x1e, 0xb, 0x3, 0x3, 0x3, 0x2, 0x3, 0x4, 0x4, 
    0x2, 0x4, 0x2, 0x2, 0x22, 0x2, 0x6, 0x3, 0x2, 0x2, 0x2, 0x4, 0x12, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0x7, 0x5, 0x4, 0x3, 0x2, 0x7, 0x8, 0x7, 0x2, 0x2, 
    0x3, 0x8, 0x3, 0x3, 0x2, 0x2, 0x2, 0x9, 0xa, 0x8, 0x3, 0x1, 0x2, 0xa, 
    0x13, 0x7, 0x3, 0x2, 0x2, 0xb, 0x13, 0x7, 0x4, 0x2, 0x2, 0xc, 0xd, 0x7, 
    0x7, 0x2, 0x2, 0xd, 0x13, 0x5, 0x4, 0x3, 0x6, 0xe, 0xf, 0x7, 0x9, 0x2, 
    0x2, 0xf, 0x10, 0x5, 0x4, 0x3, 0x2, 0x10, 0x11, 0x7, 0x8, 0x2, 0x2, 
    0x11, 0x13, 0x3, 0x2, 0x2, 0x2, 0x12, 0x9, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x12, 0xc, 0x3, 0x2, 0x2, 0x2, 0x12, 0xe, 0x3, 
    0x2, 0x2, 0x2, 0x13, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0xc, 0x5, 
    0x2, 0x2, 0x15, 0x16, 0x7, 0x6, 0x2, 0x2, 0x16, 0x1b, 0x5, 0x4, 0x3, 
    0x6, 0x17, 0x18, 0xc, 0x4, 0x2, 0x2, 0x18, 0x19, 0x7, 0x5, 0x2, 0x2, 
    0x19, 0x1b, 0x5, 0x4, 0x3, 0x5, 0x1a, 0x14, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1a, 
    0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x5, 0x12, 0x1a, 0x1c, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

gramParser::Initializer gramParser::_init;
