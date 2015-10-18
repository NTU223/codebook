
lnt Madd(lnt a, lnt b, lnt mod) {
  return (a + b + mod) % mod;
}
lnt Mmul(lnt a, lnt b, lnt mod) {
  return (a * b) % mod;
}

int Pow(int a, int b, int mod) {
  lnt r = 1, t = a;
  for( ; b != 0;
      b >>= 1, t = Mmul(t, t, mod))
    if((b&1) != 0) r=Mmul(r, t, mod);
  return (int)r;
}

int Inverse(int a, int mod) {
  return Pow(a, mod - 2, mod);
}

void RowSwi(int coe[][MAXN+1],
            int n, int mod,
            int a, int b) {
  for(int i = 1; i <= n+1; ++i)
    swap(coe[a][i], coe[b][i]);
}

void RowMul(int coe[][MAXN + 1],
            int n, int mod,
            int a, int c) {
  for(int i=1; i<=n + 1; ++i)
    coe[a][i]=Mmul(coe[a][i],c,
                   mod);
}

void RowAdd(int coe[][MAXN + 1],
            int n, int mod,
            int a,int b,int c) {
  for(int i=1; i <= n+1; ++i)
    coe[b][i]=Madd(coe[b][i],
                   Mmul(coe[a][i],
                        c,
                        mod),
                   mod);
}

void GaussElimination(
    int n, int mod,
    int coe[][MAXN + 1]) {
  for(int j=1, k=1; j<=n; ++j){
    for(i = k; i <= n; ++i)
      if(coe[i][j] != 0) break;
    if(i > n) continue;

    RowSwi(coe, n, mod, i, k);
    RowMul(coe, n, mod, k,
           Inverse(coe[k][j], mod));
    for(i = 1; i <= n; ++i) {
      if(i == k) continue;
      RowAdd(coe, n, mod, k, i,
             Madd(mod,
                  -coe[i][j],
                  mod));
    }
    ++k;
  }
}
