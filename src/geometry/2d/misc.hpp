#ifndef STDLIB_2D_MISC_HPP
#define STDLIB_2D_MISC_HPP
#include "geo.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "segment.hpp"

namespace ClosestPair {
using P = Point<ll>;
pair<P, P> closestPair(vector<P> v) {
  assert(sz(v) > 1);
  set<P> S;
  sort(all(v), [](P a, P b) { return a.y < b.y; });
  pair<ll, pair<P, P>> ret{LLONG_MAX, {P(), P()}};
  int j = 0;
  for (P p : v) {
    P d{1 + (ll)sqrt(ret.first), 0};
    while (v[j].y <= p.y - d.x) S.erase(v[j++]);
    auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
    for (; lo != hi; ++lo) ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
    S.insert(p);
  }
  return ret.second;
}
} // namespace ClosestPair
using namespace ClosestPair;

#endif