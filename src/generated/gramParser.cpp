
// Generated from /home/david/code/bool_expr/src/gram.g4 by ANTLR 4.5.3


#include "gramBaseListener.h"

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


//----------------- ExprContext ------------------------------------------------------------------

gramParser::ExprContext::ExprContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}


ssize_t gramParser::ExprContext::getRuleIndex() const {
  return gramParser::RuleExpr;
}

void gramParser::ExprContext::copyFrom(Ref<ExprContext> const& ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AndExprContext ------------------------------------------------------------------

Ref<tree::TerminalNode> gramParser::AndExprContext::AND() {
  return getToken(gramParser::AND, 0);
}

std::vector<Ref<gramParser::ExprContext>> gramParser::AndExprContext::expr() {
  return getRuleContexts<gramParser::ExprContext>();
}

Ref<gramParser::ExprContext> gramParser::AndExprContext::expr(int i) {
  return getRuleContext<gramParser::ExprContext>((size_t)i);
}

gramParser::AndExprContext::AndExprContext(Ref<ExprContext> const& ctx) { copyFrom(ctx); }

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

//----------------- FalseLitContext ------------------------------------------------------------------

Ref<tree::TerminalNode> gramParser::FalseLitContext::FALSE() {
  return getToken(gramParser::FALSE, 0);
}

gramParser::FalseLitContext::FalseLitContext(Ref<ExprContext> const& ctx) { copyFrom(ctx); }

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

//----------------- TrueLitContext ------------------------------------------------------------------

Ref<tree::TerminalNode> gramParser::TrueLitContext::TRUE() {
  return getToken(gramParser::TRUE, 0);
}

gramParser::TrueLitContext::TrueLitContext(Ref<ExprContext> const& ctx) { copyFrom(ctx); }

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

//----------------- ParenExprContext ------------------------------------------------------------------

Ref<tree::TerminalNode> gramParser::ParenExprContext::OPEN_PAREN() {
  return getToken(gramParser::OPEN_PAREN, 0);
}

Ref<gramParser::ExprContext> gramParser::ParenExprContext::expr() {
  return getRuleContext<gramParser::ExprContext>(0);
}

Ref<tree::TerminalNode> gramParser::ParenExprContext::CLOSE_PAREN() {
  return getToken(gramParser::CLOSE_PAREN, 0);
}

gramParser::ParenExprContext::ParenExprContext(Ref<ExprContext> const& ctx) { copyFrom(ctx); }

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

//----------------- OrExprContext ------------------------------------------------------------------

Ref<tree::TerminalNode> gramParser::OrExprContext::OR() {
  return getToken(gramParser::OR, 0);
}

std::vector<Ref<gramParser::ExprContext>> gramParser::OrExprContext::expr() {
  return getRuleContexts<gramParser::ExprContext>();
}

Ref<gramParser::ExprContext> gramParser::OrExprContext::expr(int i) {
  return getRuleContext<gramParser::ExprContext>((size_t)i);
}

gramParser::OrExprContext::OrExprContext(Ref<ExprContext> const& ctx) { copyFrom(ctx); }

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


Ref<gramParser::ExprContext> gramParser::expr() {
   return expr(0);
}

Ref<gramParser::ExprContext> gramParser::expr(int precedence) {
  Ref<ParserRuleContext> parentContext = _ctx;
  int parentState = getState();
  Ref<gramParser::ExprContext> _localctx = std::make_shared<ExprContext>(_ctx, parentState);
  Ref<gramParser::ExprContext> previousContext = _localctx;
  int startState = 0;
  enterRecursionRule(_localctx, 0, gramParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    int alt;
    enterOuterAlt(_localctx, 1);
    setState(9);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case gramParser::TRUE: {
        _localctx = std::make_shared<TrueLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(3);
        match(gramParser::TRUE);
        break;
      }

      case gramParser::FALSE: {
        _localctx = std::make_shared<FalseLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(4);
        match(gramParser::FALSE);
        break;
      }

      case gramParser::OPEN_PAREN: {
        _localctx = std::make_shared<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(5);
        match(gramParser::OPEN_PAREN);
        setState(6);
        expr(0);
        setState(7);
        match(gramParser::CLOSE_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(19);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(17);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = std::make_shared<AndExprContext>(std::make_shared<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(11);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(12);
          match(gramParser::AND);
          setState(13);
          std::dynamic_pointer_cast<AndExprContext>(_localctx)->r = expr(4);
          break;
        }

        case 2: {
          auto newContext = std::make_shared<OrExprContext>(std::make_shared<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(14);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(15);
          match(gramParser::OR);
          setState(16);
          std::dynamic_pointer_cast<OrExprContext>(_localctx)->r = expr(3);
          break;
        }

        } 
      }
      setState(21);
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

bool gramParser::sempred(Ref<RuleContext> const& context, int ruleIndex, int predicateIndex) {
  switch (ruleIndex) {
    case 0: return exprSempred(std::dynamic_pointer_cast<ExprContext>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool gramParser::exprSempred(Ref<ExprContext> const& _localctx, int predicateIndex) {
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
  "expr"
};

std::vector<std::string> gramParser::_literalNames = {
  "", "'tru'", "'false'", "'or'", "'and'"
};

std::vector<std::string> gramParser::_symbolicNames = {
  "", "TRUE", "FALSE", "OR", "AND", "CLOSE_PAREN", "OPEN_PAREN"
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
    0x3, 0x8, 0x19, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0xc, 0xa, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x14, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x17, 0xb, 0x2, 0x3, 0x2, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x2, 0x2, 0x1b, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4, 0x5, 0x8, 0x2, 
    0x1, 0x2, 0x5, 0xc, 0x7, 0x3, 0x2, 0x2, 0x6, 0xc, 0x7, 0x4, 0x2, 0x2, 
    0x7, 0x8, 0x7, 0x8, 0x2, 0x2, 0x8, 0x9, 0x5, 0x2, 0x2, 0x2, 0x9, 0xa, 
    0x7, 0x7, 0x2, 0x2, 0xa, 0xc, 0x3, 0x2, 0x2, 0x2, 0xb, 0x4, 0x3, 0x2, 
    0x2, 0x2, 0xb, 0x6, 0x3, 0x2, 0x2, 0x2, 0xb, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x15, 0x3, 0x2, 0x2, 0x2, 0xd, 0xe, 0xc, 0x5, 0x2, 0x2, 0xe, 0xf, 
    0x7, 0x6, 0x2, 0x2, 0xf, 0x14, 0x5, 0x2, 0x2, 0x6, 0x10, 0x11, 0xc, 
    0x4, 0x2, 0x2, 0x11, 0x12, 0x7, 0x5, 0x2, 0x2, 0x12, 0x14, 0x5, 0x2, 
    0x2, 0x5, 0x13, 0xd, 0x3, 0x2, 0x2, 0x2, 0x13, 0x10, 0x3, 0x2, 0x2, 
    0x2, 0x14, 0x17, 0x3, 0x2, 0x2, 0x2, 0x15, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x15, 0x16, 0x3, 0x2, 0x2, 0x2, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 0x17, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x5, 0xb, 0x13, 0x15, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  for (int i = 0; i < _atn.getNumberOfDecisions(); i++) { 
    _decisionToDFA.push_back(dfa::DFA(_atn.getDecisionState(i), i));
  }
}

gramParser::Initializer gramParser::_init;
