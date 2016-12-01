#include "rewriter.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

namespace Rewrite {
using namespace std::placeholders;

using namespace std::placeholders;
  
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

auto sequence_(Strat s1, Strat s2) {
  return std::bind(&Sequence::operator(), Sequence{s1, s2}, _1);
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

auto choice_(Strat s1, Strat s2) {
  return std::bind(&Choice::operator(), Choice{s1, s2}, _1);
}

optional<ref_t<AST::Expr>> Not::operator()(ref_t<AST::Expr> const &expr) {
  // cerr << "NOT" << std::endl;
  if (auto r1 = s1(expr); !r1) {
    return expr;
  } else {
    return boost::none;
  }
}

auto not_(Strat s1) { return std::bind(&Not::operator(), Not{s1}, _1); }

optional<ref_t<AST::Expr>> Try::operator()(ref_t<AST::Expr> expr) {
  // cerr << "TRY" << std::endl;
  return choice_(s, &Identity)(expr);
}

auto try_(Strat s1) { return std::bind(&Try::operator(), Try{s1}, _1); }

// Try(Sequence(S, Repeat(S)))
optional<ref_t<AST::Expr>> Repeat::operator()(ref_t<AST::Expr> expr) {
  // cerr << "REPEAT" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return try_(sequence_(s, self))(expr);
}

auto repeat_(Strat s1) {
  return std::bind(&Repeat::operator(), Repeat{s1}, _1);
}
struct All {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr) {
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
};

auto all_(Strat s1) { return std::bind(&All::operator(), All{s1}, _1); }

struct One {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr) {
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
    if (auto r = find_if(
            begin(args), end(args),
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
};
auto one_(Strat s1) { return std::bind(&One::operator(), One{s1}, _1); }

// BottomUp(S) = Sequence(All(BottomUp(S)), S)
struct BottomUp {
  Strat s;
  optional<ref_t<AST::Expr>> operator()(ref_t<AST::Expr> expr) {
    // cerr << "BOTTOMUP" << std::endl;
    auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };

    return sequence_(all_(self), s)(expr);
  }
};

auto bottomUp_(Strat s1) {
  return std::bind(&BottomUp::operator(), BottomUp{s1}, _1);
}

// TopDown(S) = Sequence(S, All(TopDown(S)))

optional<ref_t<AST::Expr>> TopDown::operator()(ref_t<AST::Expr> expr) {
  // cerr << "TOPDOWN" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return sequence_(s, all_(self))(expr);
}

auto topDown_(Strat s1) {
  return std::bind(&TopDown::operator(), TopDown{s1}, _1);
}

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
optional<ref_t<AST::Expr>> OnceBottomUp::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ONE_BOTTOM_UP" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return choice_(one_(self), s)(expr);
}

auto onceBottomUp_(Strat s1) {
  return std::bind(&OnceBottomUp::operator(), OnceBottomUp{s1}, _1);
}

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
optional<ref_t<AST::Expr>> OnceTopDown::operator()(ref_t<AST::Expr> expr) {
  // cerr << "ONCE_TOP_DOWN" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return choice_(s, one_(self))(expr);
}

auto onceTopDown_(Strat s1) {
  return std::bind(&OnceTopDown::operator(), OnceTopDown{s1}, _1);
}

optional<ref_t<AST::Expr>> Innermost::operator()(ref_t<AST::Expr> expr) {
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  // cerr << "INNER MOST" << std::endl;
  return repeat_(onceBottomUp_(s))(expr);
}

auto innermost_(Strat s1) {
  return std::bind(&Innermost::operator(), Innermost{s1}, _1);
}

optional<ref_t<AST::Expr>> Outermost::operator()(ref_t<AST::Expr> expr) {
  // cerr << "OUTTER_MOST" << std::endl;
  auto self = [this](ref_t<AST::Expr> arg) { return (*this)(arg); };
  return repeat_(onceTopDown_(s))(expr);
}

auto outermost_(Strat s1) {
  return std::bind(&Outermost::operator(), Outermost{s1}, _1);
}
} // end Namespace
