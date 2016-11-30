#include <algorithm>
#include <boost/optional/optional.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <type_traits>
#include <vector>

template <class T> using optional = boost::optional<T>;

using namespace std;

namespace AST {
enum class nature { Not, LitT, LitF, And, Or };

template <class T> using ref_t = std::shared_ptr<T>;

struct Expr {

  Expr *parent = nullptr;
  virtual ~Expr() = 0;
  Expr(Expr *p, nature nn) : parent(p), n(nn) {}
  virtual std::string toString() const = 0;
  nature what() const { return n; };
  const nature n;

  virtual std::vector<ref_t<AST::Expr>> children() const = 0;
  virtual ref_t<AST::Expr> clone(std::vector<ref_t<AST::Expr>> args) const = 0;
};
Expr::~Expr() {}

struct Not : Expr {
  ref_t<AST::Expr> e;
  Not(ref_t<AST::Expr> ee) : Expr{this, nature::Not}, e(ee) {}
  std::string toString() const override { return "!("s + e->toString() + ")"; }
  std::vector<ref_t<AST::Expr>> children() const override { return {e}; }
  ref_t<AST::Expr> clone(std::vector<ref_t<AST::Expr>> args) const override {
    return std::make_shared<Not>(args[0]);
  }
};

struct BoolLit : Expr {
  bool b;
  BoolLit(bool bb) : Expr{this, bb ? nature::LitT : nature::LitF}, b(bb) {}
  std::string toString() const override {
    std::ostringstream os;
    os << b;
    return os.str();
  }
  std::vector<ref_t<AST::Expr>> children() const override { return {}; }
  ref_t<AST::Expr> clone(std::vector<ref_t<AST::Expr>> args) const override {
    return std::make_shared<BoolLit>(b);
  }
};

struct And : Expr {
  ref_t<AST::Expr> l;
  ref_t<AST::Expr> r;
  And(ref_t<AST::Expr> ll, ref_t<AST::Expr> rr)
      : Expr{this, nature::And}, l((ll)), r((rr)) {}

  std::string toString() const override {
    return std::string{"("} + l->toString() + "&&" + r->toString() + ")";
  }
  std::vector<ref_t<AST::Expr>> children() const override { return {l, r}; }
  ref_t<AST::Expr> clone(std::vector<ref_t<AST::Expr>> args) const override {
    return std::make_shared<And>(args[0], args[1]);
  }
};

struct Or : Expr {
  ref_t<AST::Expr> l;
  ref_t<AST::Expr> r;
  Or(ref_t<AST::Expr> ll, ref_t<AST::Expr> rr)
      : Expr{this, nature::Or}, l((ll)), r((rr)) {}
  std::string toString() const override {
    return "("s + l->toString() + "||" + r->toString() + ")";
  }
  std::vector<ref_t<AST::Expr>> children() const override { return {l, r}; }
  ref_t<AST::Expr> clone(std::vector<ref_t<AST::Expr>> args) const override {
    return std::make_shared<Or>(args[0], args[1]);
  }
};

//================================================================================
std::ostream &operator<<(std::ostream &o, const Expr &e) {
  o << e.toString();
  return o;
}
}

template <class T> optional<AST::ref_t<AST::Expr>> some(T e) {
  return optional<AST::ref_t<AST::Expr>>(e);
}

namespace Rewrite {
using namespace std::placeholders;

using Strat = std::function<optional<AST::ref_t<AST::Expr>>(
    AST::ref_t<AST::Expr> const &)>;

optional<AST::ref_t<AST::Expr>> Identity(AST::ref_t<AST::Expr> const &e) {
  return e;
}

struct Sequence {
  Strat s1;
  Strat s2;

  optional<AST::ref_t<AST::Expr>>
  operator()(AST::ref_t<AST::Expr> const &expr) const {
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
};

auto sequence_(Strat s1, Strat s2) {
  return std::bind(&Sequence::operator(), Sequence{s1, s2}, _1);
}

struct Choice {
  Strat s1;
  Strat s2;
  optional<AST::ref_t<AST::Expr>>
  operator()(AST::ref_t<AST::Expr> const &expr) const {
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
};

auto choice_(Strat s1, Strat s2) {
  return std::bind(&Choice::operator(), Choice{s1, s2}, _1);
}
struct Not {
  Strat s1;
  optional<AST::ref_t<AST::Expr>>
  operator()(AST::ref_t<AST::Expr> const &expr) {
    // cerr << "NOT" << std::endl;
    if (auto r1 = s1(expr); !r1) {
      return expr;
    } else {
      return boost::none;
    }
  }
};
auto not_(Strat s1) { return std::bind(&Not::operator(), Not{s1}, _1); }

struct Try {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "TRY" << std::endl;
    return choice_(s, &Identity)(expr);
  }
};

auto try_(Strat s1) { return std::bind(&Try::operator(), Try{s1}, _1); }

struct Repeat {
  Strat s;

  // Try(Sequence(S, Repeat(S)))
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "REPEAT" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    return try_(sequence_(s, self))(expr);
  }
};
auto repeat_(Strat s1) {
  return std::bind(&Repeat::operator(), Repeat{s1}, _1);
}
struct All {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "ALL" << std::endl;
    auto children = expr->children();
    std::vector<optional<AST::ref_t<AST::Expr>>> args;
    // cerr << *expr << " \n SIZE" << children.size() << std::endl;
    std::transform(begin(children), end(children), std::back_inserter(args),
                   [this](AST::ref_t<AST::Expr> sub) { return s(sub); });
    if (std::all_of(begin(args), end(args), [](auto const &result) -> bool {
          return static_cast<bool>(result);
        })) {
      std::vector<AST::ref_t<AST::Expr>> args2;
      std::transform(
          begin(children), end(children), std::back_inserter(args),
          [this](optional<AST::ref_t<AST::Expr>> sub) { return *sub; });
      return expr->clone(args2);
    } else {
      return boost::none;
    }
  }
};

auto all_(Strat s1) { return std::bind(&All::operator(), All{s1}, _1); }

struct One {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "ONE ON " << *expr << std::endl;
    auto children = expr->children();
    std::vector<optional<AST::ref_t<AST::Expr>>> args;
    // cout << "SIZE " << children.size() << "\n";
    for (auto e : children) {
      // cerr << "## " << *e << std::endl;
    }
    std::transform(begin(children), end(children), std::back_inserter(args),
                   [this](AST::ref_t<AST::Expr> sub) {
                     // cerr << *sub << std::endl;
                     return s(sub);
                   });
    if (auto r = find_if(
            begin(args), end(args),
            [](auto const &result) { return static_cast<bool>(result); });
        r != end(args)) {
      // cerr << "ONE CHILD MATCH" << std::endl;
      std::vector<AST::ref_t<AST::Expr>> args2;
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
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "BOTTOMUP" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };

    return sequence_(all_(self), s)(expr);
  }
};

auto bottomUp_(Strat s1) {
  return std::bind(&BottomUp::operator(), BottomUp{s1}, _1);
}

// TopDown(S) = Sequence(S, All(TopDown(S)))
struct TopDown {

  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "TOPDOWN" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    return sequence_(s, all_(self))(expr);
  }
};
auto topDown_(Strat s1) {
  return std::bind(&TopDown::operator(), TopDown{s1}, _1);
}

// OnceBottomUp(S) = Choice(One(OnceBottomUp(S)), S)
struct OnceBottomUp {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "ONE_BOTTOM_UP" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    return choice_(one_(self), s)(expr);
  }
};
auto onceBottomUp_(Strat s1) {
  return std::bind(&OnceBottomUp::operator(), OnceBottomUp{s1}, _1);
}

//  OnceTopDown(S)  = Choice(S, One(OnceTopDown(S)))
struct OnceTopDown {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "ONCE_TOP_DOWN" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    return choice_(s, one_(self))(expr);
  }
};
auto onceTopDown_(Strat s1) {
  return std::bind(&OnceTopDown::operator(), OnceTopDown{s1}, _1);
}

// Innermost(S) = Repeat(OnceBottomUp(S))
struct Innermost {
  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    // std::function<optional<AST::ref_t<AST::Expr>>(AST::ref_t<AST::Expr>)>
    // self =
    //     std::bind(&Innermost::operator(), this, _1);
    // cerr << "INNER MOST" << std::endl;
    return repeat_(onceBottomUp_(s))(expr);
  }
};
auto innermost_(Strat s1) {
  return std::bind(&Innermost::operator(), Innermost{s1}, _1);
}

//  Outermost(S)    = Repeat(OnceTopDown(S))
struct Outermost {

  Strat s;
  optional<AST::ref_t<AST::Expr>> operator()(AST::ref_t<AST::Expr> expr) {
    // cerr << "OUTTER_MOST" << std::endl;
    auto self = [this](AST::ref_t<AST::Expr> arg) { return (*this)(arg); };
    return repeat_(onceTopDown_(s))(expr);
  }
};
auto outermost_(Strat s1) {
  return std::bind(&Outermost::operator(), Outermost{s1}, _1);
}
}

#define try_downcast(name, T, expr)                                            \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)))

#define try_downcastCond(name, T, expr, cond)                                  \
  if (auto(name) = std::dynamic_pointer_cast<T>((expr));                       \
      static_cast<bool>((name)) && (cond))

// #define try_downcast2(name, T, expr)                                           \
//   if (auto name = dynamic_cast<T const *>(&(expr)); static_cast<bool>(name))

optional<AST::ref_t<AST::Expr>> PushNot(AST::ref_t<AST::Expr> const &e) {
  using namespace AST;
  try_downcast(notE, AST::Not, e) {
    try_downcast(subOr, AST::Or, notE->e) {
      auto ret = make_shared<And>(make_shared<AST::Not>(subOr->l),
                                  make_shared<AST::Not>(subOr->r));

      return some(ret);
    }
    else try_downcast(subAnd, AST::And, notE->e) {
      return some(make_shared<Or>(make_shared<Not>(subAnd->l),
                                  make_shared<Not>(subAnd->r)));
    }
  }
  // cerr << "failed" << std::endl;
  return boost::none;
}

optional<AST::ref_t<AST::Expr>> simplify(AST::ref_t<AST::Expr> const &e) {
  using namespace AST;

  try_downcast(andE, AST::And, e) {
    try_downcastCond(lit, AST::BoolLit, andE->l, lit->what() == nature::LitF) {
      return some(make_shared<AST::BoolLit>(false));
    }
    else try_downcastCond(lit, AST::BoolLit, andE->r,
                          lit->what() == nature::LitF) {
      return some(make_shared<AST::BoolLit>(false));
    }
  }

  try_downcast(orE, AST::Or, e) {
    try_downcastCond(lit, AST::BoolLit, orE->l, lit->what() == nature::LitT) {
      return some(make_shared<AST::BoolLit>(true));
    }
    else try_downcastCond(lit, AST::BoolLit, orE->r,
                          lit->what() == nature::LitT) {
      return some(make_shared<AST::BoolLit>(true));
    }
  }

  try_downcast(notE, AST::Not, e) {
    try_downcast(lit, AST::BoolLit, notE->e) {
      return some(make_shared<AST::BoolLit>(!lit->b));
    }
  }

  // cerr << "failed" << std::endl;
  return boost::none;
}

int main(int argc, char *argv[]) {
  using namespace AST;

  auto t = make_shared<Not>(make_shared<And>(
      make_shared<Not>(make_shared<BoolLit>(true)),
      make_shared<Or>(make_shared<BoolLit>(true),
                      make_shared<Not>(make_shared<BoolLit>(false)))));

  cerr << *t << std::endl;

  using namespace Rewrite;
  cerr << "BEGIN"
       << "\n\n";
  auto strat = outermost_(choice_(&PushNot, &simplify));

  if (auto r = strat(t); r) {
    cerr << **r << std::endl;
  }

  return 0;
}
