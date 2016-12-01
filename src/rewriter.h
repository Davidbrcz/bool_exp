#ifndef REWRITER_H
#define REWRITER_H

#include "expr.h"

namespace Rewrite {

using Strat =
    std::function<optional<ref_t<AST::Expr>>(ref_t<AST::Expr> const &)>;

optional<ref_t<AST::Expr>> Identity(ref_t<AST::Expr> const &e);

struct Sequence {
  Strat s1;
  Strat s2;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
};

auto sequence_(Strat s1, Strat s2);

struct Choice {
  Strat s1;
  Strat s2;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
};

auto choice_(Strat s1, Strat s2);

struct Not {
  Strat s1;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
};
auto not_(Strat s1);

struct Try {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto try_(Strat s1);

struct Repeat {
  Strat s;

  // Try(Sequence(S, Repeat(S)))
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto repeat_(Strat s1);

struct All {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto all_(Strat s1);

struct One {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto one_(Strat s1);

// BottomUp(S) = Sequence(All(BottomUp(S)), S)
struct BottomUp {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto bottomUp_(Strat s1);

// TopDown(S) = Sequence(S, All(TopDown(S)))
struct TopDown {

  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto topDown_(Strat s1);

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
struct OnceBottomUp {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto onceBottomUp_(Strat s1);
//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
struct OnceTopDown {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto onceTopDown_(Strat s1);
// Innermost(S) = Repeat(OnceBottomUp(S))
struct Innermost {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto innermost_(Strat s1);

//  Outermost(S)    = Repeat(OnceTopDown(S))
struct Outermost {

  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto outermost_(Strat s1);
}

#endif /* REWRITER_H */
