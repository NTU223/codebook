// num of v in X, num of v in Y
int nx, ny;
// party of each x/y
int mx[100], my[100];
// forest
int px[100], py[100];
// simpl... adj
bool adj[100][100];

int trace(int y) {
  int x = py[y], yy = px[x];
  py[y] = px[x] = -1;
  if (mx[x] == -1 ||
      (yy != -1 && trace(yy))){
    mx[x] = y; my[y] = x;
    return 1;
  }
  return 0;
}

int bipartite_matching() {
  memset(mx, -1, sizeof(mx));
  memset(my, -1, sizeof(my));

  int q[100], *qf, *qb;
  int c = 0;
  while (true) {
    memset(px, -1, sizeof(px));
    memset(py, -1, sizeof(py));
    qf = qb = q;

    for (int x=0; x<nx; ++x)
      if (mx[x] == -1) {
        *qb++ = x;
        // px[x] = -2;
      }

    bool ap = false;
    for (int* tqb=qb;
         qf<tqb && !ap; tqb = qb)
      for(int x=*qf++,y=0;y<ny;++y)
        if (adj[x][y]
            /*&& mx[x] != y*/
            && py[y] == -1){
          py[y] = x;
          if (my[y] == -1)
            ap = true;
          else *qb++ = my[y],
            px[my[y]] = y;
        }
    if (!ap) break;

    for (int y=0; y<ny; ++y)
      if (my[y]==-1 && py[y]!=-1)
        c += trace(y);
  }
  return c;
}

