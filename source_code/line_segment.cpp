struct Segment{
  Vector2D a, b;

  Segment&operator()(const Vector2D& __a, const Vector2D& __b){
    a = __a; b = __b;
    return *this;
  }

  double dist(const Vector2D& p) const {
    if((b - a).dot(p - a) <= 0) return (p - a).length();
    if((a - b).dot(p - b) <= 0) return (p - b).length();
    return fabs((b - a).cross(p - a)) / (b - a).length();
  }
  double dist(const Segment& s) const {
    if(cross(s)) return 0;
    return min(min(min(
                (a - s.a).length(),
                (a - s.b).length()),
            (b - s.a).length()),
        (b - s.b).length());
  }
  bool onA(const Vector2D& p) const {
    return ((a - p).cross(b - p) == 0 &&
            (a - p).dot(b - p) <= 0 && p != b);
  }
  bool onB(const Vector2D& p) const {
    return ((a - p).cross(b - p) == 0 &&
            (a - p).dot(b - p) <= 0 && p != a);
  }
  bool onAB(const Vector2D& p) const {
    return ((a - p).cross(b - p) == 0 && (a - p).dot(b - p) <= 0);
  }
  bool cross(const Segment& s) const {
    double c1 = (b - a).cross(s.a - a);
    double c2 = (b - a).cross(s.b - a);
    double c3 = (s.b - s.a).cross(a - s.a);
    double c4 = (s.b - s.a).cross(b - s.a);
    return (c1 * c2 <= 0 && c3 * c4 <= 0);
  }
};

struct Line{
  Vector2D a, b;

  Line(){ }
  Line(const Vector2D &__a, const Vector2D &__b): a(__a), b(__b) { }
  Line(const Line &l)                           : a(l.a), b(l.b) { }
  Line(const Segment &s)                        : a(s.a), b(s.b) { }

  Line&operator()(const Vector2D& __a, const Vector2D& __b){
    a = __a; b = __b;
    return *this;
  }

  double dist(const Vector2D& p) const {
    return fabs((b - a).cross(p - a)) / (b - a).length();
  }
  double dist(const Line& l) const {
    if((b - a).cross(l.b - l.a) != 0) return 0;
    return dist(l.a);
  }

  Vector2D inter(const Line& l) const {
    Vector2D u = b - a, v = l.b - l.a, w = l.a - a;
    if(u.cross(v) == 0) return Vector2D(DNF, DNF);
    return a + u * w.cross(v) / u.cross(v);
  }
};
