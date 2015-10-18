struct SimplePolygon{
  Vector2Ds verts;
  int create(const Vector2Ds& pos, int N){
    verts.clear();
    for(int i = 0; i < N; i++){
      int pre = (i - 1 + N) % N;
      int nxt = (i + 1 + N) % N;
      if((pos[pre] - pos[i]).cross(pos[nxt] - pos[i]) == 0) continue;
      verts.push_back(pos[i]);
    }
    return verts.size();
  }
  Vector2D findG() const {
    int sz = verts.size();
    Vector2D p(0, 0);
    if(sz <= 3){
      for(int i = 0, ii = verts.size(); i < ii; i++) p += verts[i];
      return p / (double)sz;
    }
    double all = 0, delta;
    for(int i = 1; i + 1 < sz; i++){
      delta = (verts[i] - verts[0]).cross(verts[i + 1] - verts[0]);
      p += (verts[0] +verts[i] + verts[i + 1]) * delta / 3.0;
      all += delta;
    }
    return p / all;
  }
  bool isIn(const Vector2D &b) const {
    bool odd = false;
    for(int i = 0, ii = verts.size(); i < ii; i++){
      const Vector2D &v1 = verts[i];
      const Vector2D &v2 = verts[(i + 1) % ii];
      if((b - v1).dot  (v2 - v1) >= 0 &&
         (b - v2).dot  (v1 - v2) >= 0 &&
         (b - v1).cross(v1 - v2) == 0) return true;
      if(v1.y < b.y && b.y <= v2.y && (v2 - v1).cross(b - v1) > 0 ||
         v2.y < b.y && b.y <= v1.y && (v1 - v2).cross(b - v2) > 0)
        odd = !odd;
    }
    return (odd == true);
  }
  double area() const {
    double ret = 0;
    for(int i = 0, ii = verts.size(); i < ii; i++){
      ret += verts[i].cross(verts[(i + 1) % ii]);
    }
    return 0.5 * ret;
  }
  double area2() const {
    double ret = 0;
    for(int i = 0, ii = verts.size(); i < ii; i++){
      ret += verts[i].cross(verts[(i + 1) % ii]);
    }
    return ret;
  }
};
struct ConvexPolygon : SimplePolygon{
  int create(Vector2Ds& pos, int N){
    sort(pos.begin(), pos.begin() + N, sort_xy);
    verts.clear();
    int top0 = 0, top = -1;
    for(int i = 0; i < N; i++){
      while(top-1>=top0 && (verts[top]-verts[top-1]).cross(pos[i]-verts[top-1]) <= 0){
        verts.pop_back(); top--;
      }
      verts.push_back(pos[i]); top++;
    }
    top0 = top;
    for(int i = N - 2; i >= 0; i--){
      while(top-1>=top0 && (verts[top]-verts[top-1]).cross(pos[i]-verts[top-1]) <= 0){
        verts.pop_back(); top--;
      }
      verts.push_back(pos[i]); top++;
    }
    verts.pop_back();
    return verts.size();
  }
};
