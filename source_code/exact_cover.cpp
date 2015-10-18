const int SIZE_N = 200 + 10;
const int SIZE_M = SIZE_N;
const int INF = 1000000000;

struct node {
  int U, D, L, R;
  node(int U = 0, int D = 0,
       int L = 0, int R = 0)
      : U(U), D(D), L(L), R(R) {}
};
struct DLX {
  int n, m;
  int cnt[SIZE_M];
  node ary[SIZE_N][SIZE_M];

  void init(int _n, int _m,
            int mat[SIZE_N][SIZE_M]) {
    n = _n, m = _m;
    for(int i = 0; i <= m; ++i)
      cnt[i] = (i == 0 ? m : 0);
    for(int i = 0; i <= n; ++i)
      for(int j = 0; j <= m; ++j)
        ary[i][j] = node(i, i, j, j);

    for(int i = 0; i <= m; ++i)
      ary[0][i].L = (i+m) % (m+1),
          ary[0][i].R=(i+1) % (m+1);

    for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= m; ++j)
        if(mat[i][j] != 0) {
          ++cnt[j];
          ary[i][j].D=0;
          ary[i][j].U=ary[0][j].U;
          ary[ary[i][j].U][j].D=i;
          ary[0][j].U=i;
        }
    for(int i=1, j, st, las; i <= n; ++i)
      for(st=las=-1, j=1; j <= m; ++j)
        if(mat[i][j] == 0) continue;
        else if(las == -1) st=las=j;
        else {
          ary[i][j].L=las, ary[i][j].R=st;
          ary[i][st].L=ary[i][las].R=j;
          las=j;
        }}
  void del(int col) {
    int r=0, c = col;
    ary[0][ary[0][c].L].R=ary[0][c].R;
    ary[0][ary[0][c].R].L=ary[0][c].L;
    for(r=ary[0][c].D;
        r != 0; r=ary[r][c].D)
      for(c=ary[r][c].R;
          c != col; c=ary[r][c].R) {
        ary[ary[r][c].U][c].D=ary[r][c].D;
        ary[ary[r][c].D][c].U=ary[r][c].U;
        --cnt[c];
      }}
  void add(int col) {
    int r = 0, c = col;
    for(r=ary[r][c].U;
        r!=0; r=ary[r][c].U)
      for(c=ary[r][c].L;
          c!=col; c=ary[r][c].L) {
        ary[ary[r][c].U][c].D=r;
        ary[ary[r][c].D][c].U=r;
        ++cnt[c];
      }
    ary[0][ary[0][c].L].R=
        ary[0][ary[0][c].R].L=c;
  }
  int find_EC() {
    if(ary[0][0].L == 0 &&
       ary[0][0].R == 0) return 0;
    int r = 0, c = 0, ret = INF;
    int min = INF, minp = -1;
    for(c=ary[0][0].R;
        c != 0; c=ary[0][c].R)
      if(cnt[c] < min) min=cnt[c], minp=c;
    if(min == 0) return INF;
    del(c = minp);
    for(r=ary[0][c].D;
        r != 0; r=ary[r][c].D) {
      for(int i=ary[r][c].R;
          i != c;
          i=ary[r][i].R) del(i);
      int t = find_EC();
      if(t != INF) ret=std::min(ret, t+1);
      for(int i=ary[r][c].L;
          i != c;
          i=ary[r][i].L) add(i);
    }
    add(c);
    return ret;
  }
};
