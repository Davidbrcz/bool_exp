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

struct Sequence : private TwoArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
  using TwoArgStep::TwoArgStep;
};

struct Choice : private TwoArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
  using TwoArgStep::TwoArgStep;
  Choice(std::string s,Strat s1,Strat s2);
  std::string msg;
};

struct Not : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

struct Try : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

// Try(Sequence(S, Repeat(S)))
struct Repeat : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

struct All : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

struct One : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

// BottomUp(S) = Sequence(All(BottomUp(S)), S)
struct BottomUp : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

// TopDown(S) = Sequence(S, All(TopDown(S)))
struct TopDown : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
  struct OnceBottomUp //: private OneArgStep
{
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  //  using OneArgStep::OneArgStep;
};

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
  struct OnceTopDown //: private OneArgStep
{
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  //using OneArgStep::OneArgStep;
};

// Innermost(S) = Repeat(OnceBottomUp(S))
struct Innermost : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};

//  Outermost(S)    = Repeat(OnceTopDown(S))
struct Outermost : private OneArgStep {
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
  using OneArgStep::OneArgStep;
};
}

#endif /* REWRITER_H */
