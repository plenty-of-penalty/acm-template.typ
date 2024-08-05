#ifndef STDLIB_2D_SEGMENT_HPP
#define STDLIB_2D_SEGMENT_HPP
#include "./geo.hpp"

namespace SegDist {
typedef Point<double> P;
double segDist(const P &s, const P &e, const P &p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2();
  auto t = min(d, max(.0, (p - s).dot(e - s))); // 全整数时用0ll代替.0即可
  return ((p - s) * d - (e - s) * t).dist() / d;
}
} // namespace SegDist
using namespace SegDist;

namespace OnSegment {
template <class P> bool onSegment(const P &s, const P &e, const P &p) {
  // 当使用Point<double>时，需要改为segDist(s,e,p)<eps
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
} // namespace OnSegment
using namespace OnSegment;

namespace SideOf {
template <class P> int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template <class P> int sideOf(const P &s, const P &e, const P &p, double eps) {
  auto a = (e - s).cross(p - s);
  double l = (e - s).dist() * eps;
  return (a > l) - (a < -l);
}
} // namespace SideOf
using namespace SideOf;

namespace SegInter {
template <class P> vector<P> segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) // 交点是不在端点上的点
    return {(a * ob - b * oa) / (ob - oa)};
  // 考虑两条线段部分重合或交在端点上的情况
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {all(s)};
}
} // namespace SegInter
using namespace SegInter;

namespace LinearTrans {
typedef Point<double> P;
P linearTrans(const P &p0, const P &p1, const P &q0, const P &q1, const P &r) {
  P dp = p1 - p0, dq = q1 - q0, num(dp.cross(dq), dp.dot(dq));
  return q0 + P((r - p0).cross(num), (r - p0).dot(num)) / dp.dist2();
}
} // namespace LinearTrans
using namespace LinearTrans;

#endif