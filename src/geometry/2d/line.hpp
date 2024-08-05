#ifndef STDLIB_2D_LINE_HPP
#define STDLIB_2D_LINE_HPP
#include "./geo.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace LineDist {
template <class P>                                    //
double lineDist(const P &a, const P &b, const P &p) { //
  return (double)(b - a).cross(p - a) / (b - a).dist();
}
} // namespace LineDist
using namespace LineDist;

namespace LineInter {
template <class P> //
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // 如果平行或重叠
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}
} // namespace LineInter
using namespace LineInter;

#endif