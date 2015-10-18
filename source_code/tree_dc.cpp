#include <algorithm>
#include <vector>

using std::max;
using std::vector;

int n;
std::vector< int > edg[SIZE_N];

int exi[SIZE_N];
int sons[SIZE_N], mson[SIZE_N];

int find_G(int now, int fa, int siz) {
  if (mson[now] * 2 <= siz &&
      (siz - sons[now]) * 2 <= siz)
    return now;
  for(int i=0; i<edg[now].size(); ++i) {
    int ne = edg[now][i];
    if(exi[ne] == 0 || ne == fa)
      continue;
    int t = find_G(ne, now, siz);
    if(t != -1) return t;
  }
  return -1;
}

void calc_son(int now, int fa) {
  sons[now] = 1, mson[now] = 0;
  for(int i=0; i<edg[now].size(); ++i) {
    int ne = edg[now][i];
    if(exi[ne] == 0 || ne == fa)
      continue;
    calc_son(ne, now);
    sons[now] += sons[ne];
    mson[now] =max(mson[now], sons[ne]);
  }
}

void TDC(int now) {
  calc_son(now, 0);
  now = find_G(now, 0, sons[now]);
  exi[now] = 0;
  for(int i=0; i<edg[now].size(); ++i) {
    int ne = edg[now][i];
    if(exi[ne] == 0) continue;
    TDC(ne);
  }
  /* do something */
  exi[now] = 1;
}
