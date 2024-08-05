#ifndef STDLIB_2D_GEO_HPP
#define STDLIB_2D_GEO_HPP
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define sz(x) (x).size()
using namespace std;
using ll = long long;
using lf = long double;

namespace geo {
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
  using P = Point;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  friend ostream &operator<<(ostream &os, P p) { //
    return os << "(" << p.x << "," << p.y << ")";
  }
  bool operator<(P p) const { //
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator==(P p) const { //
    return tie(x, y) == tie(p.x, p.y);
  }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  double angle() const {
    return atan2(y, x); // 返回弧度制(已经乘过pi了)
  }
  P perp() const { // 逆时针旋转90°
    return P(-y, x);
  }
  P rotate(double a) const { // 逆时针旋转a(弧度制)
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
};
} // namespace geo
using namespace geo;

#endif