#ifndef REWRITER_H
#define REWRITER_H

#include "expr.h"

namespace Rewrite {
using namespace std::placeholders;
using Strat =
    std::function<optional<ref_t<AST::Expr>>(ref_t<AST::Expr> const &)>;

optional<ref_t<AST::Expr>> Identity(ref_t<AST::Expr> const &e);

struct TwoArgStep {
protected:
  Strat s1;
  Strat s2;
  ~TwoArgStep() = default;

public:
  TwoArgStep(Strat ss1, Strat ss2);
};

struct OneArgStep {
protected:
  Strat s;
  ~OneArgStep() = default;

public:
  OneArgStep(Strat ss1);
};

struct Sequence : TwoArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
  using TwoArgStep::TwoArgStep;
};

struct Choice : TwoArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
  using TwoArgStep::TwoArgStep;
};

struct Not : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

struct Try : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

// Try(Sequence(S, Repeat(S)))
struct Repeat : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

struct All : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

struct One : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

// BottomUp(S) = Sequence(All(BottomUp(S)), S)
struct BottomUp : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

// TopDown(S) = Sequence(S, All(TopDown(S)))
struct TopDown : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
struct OnceBottomUp : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
struct OnceTopDown : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

// Innermost(S) = Repeat(OnceBottomUp(S))
struct Innermost : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};

//  Outermost(S)    = Repeat(OnceTopDown(S))
struct Outermost : OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
  using OneArgStep::OneArgStep;
};
}

#endif /* REWRITER_H */
