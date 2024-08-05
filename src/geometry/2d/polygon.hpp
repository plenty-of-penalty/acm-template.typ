#ifndef STDLIB_2D_POLYGON_HPP
#define STDLIB_2D_POLYGON_HPP
#include "geo.hpp"
#include "line.hpp"
#include "segment.hpp"

namespace InPolygon {
using P = Point<double>;
template <class P> bool inPolygon(vector<P> &p, P a, bool strict = true) {
  int cnt = 0, n = sz(p);
  for (int i = 0; i < n; i++) {
    P q = p[(i + 1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
}
} // namespace InPolygon
using namespace InPolygon;

namespace PolygonArea {
using P = Point<double>;
template <class T> T polygonArea2(vector<Point<T>> &v) {
  T a = v.back().cross(v[0]);
  for (int i = 0; i + 1 < sz(v); i++) a += v[i].cross(v[i + 1]);
  return a;
}
} // namespace PolygonArea
using namespace PolygonArea;

namespace PolygonCenter {
using P = Point<double>;
P polygonCenter(const vector<P> &v) {
  P res(0, 0);
  double A = 0;
  for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
    res = res + (v[i] + v[j]) * v[j].cross(v[i]);
    A += v[j].cross(v[i]);
  }
  return res / A / 3;
}
} // namespace PolygonCenter
using namespace PolygonCenter;

namespace PolygonCut {
using P = Point<double>;
vector<P> polygonCut(const vector<P> &poly, P s, P e) {
  vector<P> res;
  for (int i = 0; i < sz(poly); i++) {
    P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
    bool side = s.cross(e, cur) < 0;
    if (side != (s.cross(e, prev) < 0)) res.push_back(lineInter(s, e, cur, prev).second);
    if (side) res.push_back(cur);
  }
  return res;
}
} // namespace PolygonCut
using namespace PolygonCut;

namespace ConvexHull {
using P = Point<ll>;
vector<P> convexHull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P> h(sz(pts) + 1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(all(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
} // namespace ConvexHull
using namespace ConvexHull;

namespace HullDiameter {
typedef Point<ll> P;
pair<P, P> hullDiameter(vector<P> S) {
  int n = sz(S), j = n < 2 ? 0 : 1;
  pair<ll, pair<P, P>> res({0, {S[0], S[0]}});
  for (int i = 0; i < j; i++)
    for (;; j = (j + 1) % n) {
      res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
      if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0) break;
    }
  return res.second;
}
} // namespace HullDiameter
using namespace HullDiameter;

namespace InHull {
using P = Point<ll>;
bool inHull(const vector<P> &l, P p, bool strict = true) {
  int a = 1, b = sz(l) - 1, r = !strict;
  if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r) return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}
} // namespace InHull
using namespace InHull;

#endif