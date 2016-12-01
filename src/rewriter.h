#ifndef REWRITER_H
#define REWRITER_H

#include "expr.h"

namespace Rewrite {
using namespace std::placeholders;
using Strat =
    std::function<optional<ref_t<AST::Expr>>(ref_t<AST::Expr> const &)>;

optional<ref_t<AST::Expr>> Identity(ref_t<AST::Expr> const &e);

struct Sequence {
  Strat s1;
  Strat s2;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
};

// auto const sequence_
//   return
// }
auto const sequence_ = [](Strat s1, Strat s2) {
  return std::bind(&Sequence::operator(), Sequence{s1, s2}, _1);
};

  struct Choice {
  Strat s1;
  Strat s2;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr) const;
};

auto const choice_= [](Strat s1, Strat s2) {
  return std::bind(&Choice::operator(), Choice{s1, s2}, _1);
};

struct Not {
  Strat s1;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> const &expr);
};

  auto const not_ =[](Strat s1) { return std::bind(&Not::operator(), Not{s1}, _1); };
struct Try {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

  auto const try_ =[](Strat s1) { return std::bind(&Try::operator(), Try{s1}, _1); };
struct Repeat {
  Strat s;

  // Try(Sequence(S, Repeat(S)))
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto const repeat_ =[](Strat s1) {
  return std::bind(&Repeat::operator(), Repeat{s1}, _1);
};
struct All {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

  auto const all_ =[](Strat s1) { return std::bind(&All::operator(), All{s1}, _1); };
struct One {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

  auto const one_ =[](Strat s1) { return std::bind(&One::operator(), One{s1}, _1); };
// BottomUp(S) = Sequence(All(BottomUp(S)), S)
struct BottomUp {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto const bottomUp_ =[](Strat s1) {
  return std::bind(&BottomUp::operator(), BottomUp{s1}, _1);
};
// TopDown(S) = Sequence(S, All(TopDown(S)))
struct TopDown {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto const topDown_ =[](Strat s1) {
  return std::bind(&TopDown::operator(), TopDown{s1}, _1);
};
// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
struct OnceBottomUp {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto const onceBottomUp_ =[](Strat s1) {
  return std::bind(&OnceBottomUp::operator(), OnceBottomUp{s1}, _1);
};

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
struct OnceTopDown {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto const onceTopDown_ =[](Strat s1) {
  return std::bind(&OnceTopDown::operator(), OnceTopDown{s1}, _1);
};

// Innermost(S) = Repeat(OnceBottomUp(S))
struct Innermost {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};
auto const innermost_ =[](Strat s1) {
  return std::bind(&Innermost::operator(), Innermost{s1}, _1);
};

//  Outermost(S)    = Repeat(OnceTopDown(S))
struct Outermost {

  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr);
};

auto const outermost_ =[](Strat s1) {
  return std::bind(&Outermost::operator(), Outermost{s1}, _1);
};
}

#endif /* REWRITER_H */
