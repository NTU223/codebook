#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <deque>

#define max(x,y) (x>y?(x):(y))
#define min(x,y) (x<y?(x):(y))
#define sqr(x) (x)*(x)
#define INF (1e20)
#define EPS (1e-9)

double noEps(double n){ return (n<EPS && n>-EPS)? 0 : n; }


struct Line2D{
  // member variable
  Vector2D p0, dir;
  // constructor
  Line2D() {}
  Line2D(const Vector2D& _p0, const Vector2D& _dir): p0(_p0), dir(_dir) {}
  Line2D(const Line2D& l): p0(l.p0), dir(l.dir) {}
  // function
  Vector2D norm(){ return ~dir; }
  int side(const Vector2D& v) const {
    // on line: 0, left side: 1, right side: 0
    double tmp = dir.cross(v-p0);
    return tmp == 0? 0 : (tmp > 0? 1 : -1);
  }
  double ang() const { return dir.ang(); }
  double dist(const Vector2D& v) const { return fabs(dir.cross(v-p0)) / dir.length(); }
  bool onLine(const Vector2D& v) const { return noEps(dist(v)) == 0; }
  bool parallel  (const Line2D& l) const { return dir.parallel(l.dir); }
  bool orthogonal(const Line2D& l) const { return dir.orthogonal(l.dir); }
  bool overlap   (const Line2D& l) const { return onLine(l.p0) && parallel(l); }
  bool intersect(const Line2D& l, Vector2D& v) const {
    if(parallel(l)) return false;
    double t = (l.p0-p0).cross(l.dir) / dir.cross(l.dir);
    v = p0 + dir * t;
    return true;
  }
  Vector2D intersect(const Line2D& l) const { // guarantee not parallel
    Vector2D ret = Vector2D(INF, INF);
    intersect(l, ret);
    return ret;
  }
  // debug
  void print() const { printf("line: ["); p0.print(); dir.print(); printf("]\n"); }
};

struct Circle2D{
  // member variable
  Vector2D center;
  double r;
  // constructor
  Circle2D() {}
  Circle2D(const Vector2D& _center, double _r): center(_center), r(_r) {}
  Circle2D(const Circle2D& c): center(c.center), r(c.r) {}
  // function
  int intersect(const Line2D& l, Vector2D& p1, Vector2D& p2){
    Vector2D v0 = Vector2D(l.dir);
    Vector2D v1 = Vector2D(l.p0 - center);
    double a = v0.dot(v0);
    double b = 2*(v0.dot(v1));
    double c = v1.dot(v1) - sqr(r);
    double d = noEps(b*b - 4*a*c);
    if(d < 0) return 0;
    else if(d == 0){
      p1 = l.p0 + l.dir * (-b) / (2*a);
      return 1;
    }
    else{
      p1 = l.p0 + l.dir * (-b-sqrt(d)) / (2*a);
      p2 = l.p0 + l.dir * (-b+sqrt(d)) / (2*a);
      return 2;
    }
  }
  int intersect(const Circle2D& c, Vector2D& p1, Vector2D& p2){
    if(center == c.center){
      if(noEps(r - c.r) == 0) return -1; // overlap
      else return 0;
    }
    Vector2D v0 = Vector2D((c.center - center)*2);
    double u = c.center.dot(c.center) - center.dot(center) + sqr(r) - sqr(c.r);
    if(noEps(v0.x) != 0) return intersect(Line2D(Vector2D(u/v0.x, 0), ~v0), p1, p2);
    else return intersect(Line2D(Vector2D(0, u/v0.y), ~v0), p1, p2);
  }
  // debug
  void print() const { printf("Circle: ["); center.print(); printf("%lf ]\n", r); }
};

struct Polygon2D{
  // member variable
  std::vector<Vector2D> vList;
  // constructor
  Polygon2D(){ vList.clear(); }
  Polygon2D(const std::vector<Vector2D> _vList): vList(_vList) {}
  template<class It> Polygon2D(It first, It last): vList(first, last) {}
  // member function
  void clear(){ vList.clear(); }
  void push(Vector2D v){ vList.push_back(v); }
  double area() const {
    double ret = 0.0;
    int n = (int)vList.size();
    for(int i=0; i<n-1; ++i)
      ret += vList[i].cross(vList[i+1]) * 0.5;
    ret += vList[n-1].cross(vList[0]) * 0.5;
    return ret;
  }
  Vector2D center() const {
    Vector2D ret;
    int n = (int)vList.size();
    for(int i=0; i<n-1; ++i)
      ret = ret + (vList[i] + vList[i+1]) * vList[i].cross(vList[i+1]) / 6.0;
    ret = ret + (vList[n-1] + vList[0]) * vList[n-1].cross(vList[0]) / 6.0;
    return ret;
  }
  // debug
  void print(){
    for(unsigned i=0; i<vList.size(); ++i){ vList[i].print(); printf("\n"); }
  }
};

// half plane intersection
bool cmpBySlope(Line2D line1, Line2D line2){
  return line1.ang() < line2.ang();
}
Polygon2D halfBanana(std::vector<Line2D>& lines){
  int n = (int)lines.size() + 4;
  int l, r;
  std::vector<Line2D> deq(n);
  // infinite square boundary
  lines.push_back(Line2D(Vector2D(-INF, -INF), Vector2D( 1,  0)));
  lines.push_back(Line2D(Vector2D( INF, -INF), Vector2D( 0,  1)));
  lines.push_back(Line2D(Vector2D( INF,  INF), Vector2D(-1,  0)));
  lines.push_back(Line2D(Vector2D(-INF,  INF), Vector2D( 0, -1)));
  // sort
  std::sort(lines.begin(), lines.end(), cmpBySlope);
  // find intersection result
  l = 0; r = -1;
#define deqSize (r-l+1)
  for(int i=0; i<n; ++i){
    if(deqSize > 0 && lines[i].parallel(deq[r])){
      if(lines[i].side(deq[r].p0) >= 0) continue;
      if(deqSize == 1){ deq[r] = Line2D(lines[i]); continue; }
    }
    while(deqSize > 1 && lines[i].side(deq[r].intersect(deq[r-1])) <= 0) r--;
    while(deqSize > 1 && lines[i].side(deq[l].intersect(deq[l+1])) <= 0) l++;
    if(deqSize == 1 && deq[r].ang() + M_PI < lines[i].ang()) return Polygon2D();
    deq[++r] = Line2D(lines[i]);
  }
  while(deqSize > 1 && deq[l].side(deq[r].intersect(deq[r-1])) <= 0) r--;
  if(deqSize < 3) return Polygon2D();
  // generate polygon
  Polygon2D ret;
  for(int i=l; i<r; ++i) ret.push(deq[i].intersect(deq[i+1]));
  ret.push(deq[l].intersect(deq[r]));
  return ret;
}

int main(){}
