typedef long long lnt;
const int NMAX = 25000;
using std::sort;
using std::swap;
template<class T>
inline T squ(T x);

struct Vector2D{
  lnt x, y;
  Vector2D(lnt x=0, lnt y=0);
  Vector2D(const Vector2D &b);
  ~Vector2D(){}
  Vector2D& operator =();
  Vector2D& operator+=();
  Vector2D& operator-=();
  Vector2D& operator*=();
  Vector2D& operator/=();
  int where() const {}
  lnt length2() const {}
  lnt dot  (const Vector2D&b);
  lnt cross(const Vector2D&b);
  bool operator<(
      const Vector2D&b)
      const {
    int w1=where();
    int w2=b.where();
    if(w1!=w2) return w1<w2;
    if(w1==0) return false;
    if(w1==1||w1==3||
       w1==5||w1==7)
      return length2()<
             b.length2();
    if(cross(b)>0)return true;
    if(cross(b)<0)return false;
    return length2()<b.length2();
  }
};
struct Char{
  lnt d;
  lnt cosA, sinA, B;

  Char& operator=(const Char &b);
  bool operator==(const Char&b)
      const{ return (d == b.d &&
            cosA*b.B==b.cosA*B&&
            sinA*b.B==b.sinA*B);
  }
  bool operator!=(const Char &b)
      const{}
};
inline lnt deal(int n,
                Vector2D*ps){
  Vector2D pAvr(0, 0);
  for(int i = 0; i < n; i++){
    pAvr  += ps[i];
    ps[i] *= n;
  }
  for(int i=0; i<n; i++)
    ps[i]-=pAvr;
  sort(ps, ps + n);
  lnt len2Sum = 0;
  for(int i = 0; i < n; i++)
      len2Sum +=ps[i].length2();
  return len2Sum;
}
void deal2(int n,
           const Vector2D *ps,
           lnt sc,Char *out){
 for(int i=0,j=1;
     i<n;i++,j++,j%=n){
  out[i].d = ps[i].length2()*sc;
  out[i].cosA=
      squ(ps[i].dot  (ps[j]));
  out[i].sinA=
      squ(ps[i].cross(ps[j]));
  out[i].B=ps[i].length2()*
           ps[j].length2();
}}
void preKMP(const Char*s,int N,
            int*out){
  out[1] = 0;
  for(int k=0,i=2;i<=N;i++){
    while(k>0&&s[k+1]!=s[i])
      k=out[k];
    if(s[k+1] == s[i]) k++;
    out[i] = k;
} }
bool kmp(const Char*str,int N,
         const Char*pat,int M){
  static int pre[NMAX*2+1];
  preKMP(pat, M, pre);
  for(int k = 0, i=1; i<=N;i++){
    while(k>0&&pat[k+1]!=str[i])
      k=pre[k];
    if(pat[k+1] == str[i])k++;
    if(k == M) return true;
  }
  return false;
}
int main(){
  for(int Z,zz=scanf("%d",&Z);Z--;){
    static int N;
    static Vector2D points[NMAX];
    static Vector2D ptmp[NMAX];
    static Char chars[NMAX*2+1];
    static Char schars[NMAX+1];
    static Char tmp[NMAX*2+1];
    static lnt ls;

    scanf("%d", &N);
    for(int i=0,x,y; i<N; i++){
        scanf("%d %d", &x, &y);
        points[i] = Vector2D(x,y);
    }
    ls = deal(N, points);
    deal2(N,points,1,tmp+1);
    for(int i = 1; i <= N; i++)
        tmp[N + i] = tmp[i];
    for(int T,tt=scanf("%d",&T);
        T--;){
      static int M;
      scanf("%d", &M);
      for(int i=0,x,y;i<M;i++){
          scanf("%d %d",&x,&y);
          ptmp[i]=Vector2D(x,y);
      }
      if(N != M){
        printf("No\n");
        continue;
      }
      for(int i=0;i<M;i++)
          points[i]=ptmp[i];
      lnt sls=deal(M,points);
      for(int i=1;i<=N*2;i++){
          chars[i] = tmp[i];
          chars[i].d *= sls;
      }
      deal2(M,points,ls,schars+1);
      bool ok = false;
      ok=ok||kmp(chars,N*2,schars,M);
      for(int i=0; i<M; i++){
          points[i] = ptmp[i];
          points[i].x *= -1;
      }
      deal (M,points);
      deal2(M,points,ls,schars+1);
      ok=ok||kmp(chars,N*2,schars,M);
      printf(ok ? "Yes\n":"No\n");
    }
    printf("\n");
  }
  return 0;
}
