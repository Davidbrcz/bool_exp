#include "rewriter.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

namespace Rewrite {

TwoArgStep::TwoArgStep(Strat ss1, Strat ss2) : s1(ss1), s2(ss2) {}
OneArgStep::OneArgStep(Strat ss) : s(ss) {}

optional<ref_t<AST::Expr>> Identity(ref_t<AST::Expr> const &e) { return e; }

optional<ref_t<AST::Expr>> Sequence::
operator()(ref_t<AST::Expr> const &expr) const {
  // cerr << "SEQ" << std::endl;
  if (auto r1 = s1(expr); r1) {
    if (auto r2 = s2(*r1); r2) {
      return r2;
    } else {
      return boost::none;
    }
  } else {
    return boost::none;
  }
}

optional<ref_t<AST::Expr>> Choice::
operator()(ref_t<AST::Expr> const &expr) const {
  // cerr << "CHOICE on " << *expr << std::endl;
  if (auto r1 = s1(expr); static_cast<bool>(r1) == true) {
    // cerr << "s1 OK" << std::endl;
    return r1;
  } else {
    // cout << "s1 failed" << std::endl;
    auto r2 = s2(expr);
    if (auto r2 = s2(expr); static_cast<bool>(r2) == true) {
      // cerr << "s2 OK" << std::endl;
      return r2;
    } else {
      // cerr << "both failed" << std::endl;
      return boost::none;
    }
  }
  // cerr << "WTF" << std::endl;
}

optional<ref_t<AST::Expr>> Not::operator()(ref_t<AST::Expr> const &expr) {
  // cerr << "NOT" << std::endl;
  if (auto r1 = s(expr); !r1) {
    return expr;
  } else {
    return boost::none;
  }
}

optional<ref_t<AST::Expr>> Try::operator()(ref_t<AST::Expr> expr) {
  // cerr << "TRY" << std::endl;
  return Choice(s, &Identity)(expr);
}

// Try(Sequence(S, Repeat(S)))
optional<ref_t<AST::Expr>> Repeat::operator()(ref_t<AST::Expr> expr) {
  // cerr << "REPEAT" << std::endl;
  // auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  // return try_(Sequence(s, self))(expr);

  auto fixed_point = [this](ref_t<AST::Expr> arg) {
    auto last = arg;
    auto r = s(last);
    while (r) {
      last = *r;
      r = s(last);
    }
    return optional<ref_t<AST::Expr>>{last};
  };
  return fixed_point(expr);
}

optional<ref_t<AST::Expr>> All::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ALL" << std::endl;
  auto children = expr->children();
  std::vector<optional<ref_t<AST::Expr>>> args;
  // cerr << *expr << " \n SIZE" << children.size() << std::endl;
  std::transform(begin(children), end(children), std::back_inserter(args),
                 [this](ref_t<AST::Expr> sub) { return s(sub); });
  if (std::all_of(begin(args), end(args), [](auto const &result) -> bool {
        return static_cast<bool>(result);
      })) {
    std::vector<ref_t<AST::Expr>> args2;
    std::transform(begin(children), end(children), std::back_inserter(args),
                   [this](optional<ref_t<AST::Expr>> sub) { return *sub; });
    return expr->clone(args2);
  } else {
    return boost::none;
  }
}

optional<ref_t<AST::Expr>> One::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ONE ON " << *expr << std::endl;
  auto children = expr->children();
  std::vector<optional<ref_t<AST::Expr>>> args;
  // cout << "SIZE " << children.size() << "\n";
  for (auto e : children) {
    // cerr << "## " << *e << std::endl;
  }
  std::transform(begin(children), end(children), std::back_inserter(args),
                 [this](ref_t<AST::Expr> sub) {
                   // cerr << *sub << std::endl;
                   return s(sub);
                 });
  if (auto r =
          find_if(begin(args), end(args),
                  [](auto const &result) { return static_cast<bool>(result); });
      r != end(args)) {
    // cerr << "ONE CHILD MATCH" << std::endl;
    std::vector<ref_t<AST::Expr>> args2;
    std::copy(begin(children), end(children), std::back_inserter(args2));
    args2[distance(begin(args), r)] = **r;
    return expr->clone(args2);
  } else {
    // cerr << "NO CHILD MATCH" << std::endl;
    return boost::none;
  }
}

// BottomUp(S) = Sequence(All(BottomUp(S)), S)
optional<ref_t<AST::Expr>> BottomUp::operator()(ref_t<AST::Expr> expr) {
  // cerr << "BOTTOMUP" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };

  return Sequence(All(self), s)(expr);
}

// TopDown(S) = Sequence(S, All(TopDown(S)))

optional<ref_t<AST::Expr>> TopDown::operator()(ref_t<AST::Expr> expr) {
  // cerr << "TOPDOWN" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return Sequence(s, All(self))(expr);
}

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
optional<ref_t<AST::Expr>> OnceBottomUp::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ONE_BOTTOM_UP" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return Choice(One(self), s)(expr);
}

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
optional<ref_t<AST::Expr>> OnceTopDown::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ONCE_TOP_DOWN" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return Choice(s, One(self))(expr);
}

optional<ref_t<AST::Expr>> Innermost::operator()(ref_t<AST::Expr> expr) {
  // cerr << "INNER MOST" << std::endl;
  return Repeat(OnceBottomUp(s))(expr);
}

optional<ref_t<AST::Expr>> Outermost::operator()(ref_t<AST::Expr> expr) {
  // cerr << "OUTTER_MOST" << std::endl;
  return Repeat(OnceTopDown(s))(expr);
}

} // end Namespace
