int L[maxn],R[maxn],U[maxn],D[maxn],
    S[maxn],C[maxn],sum;
void insert(int x,int c){
  /*insert element x into column c*/
  D[U[c]]=x; U[x]=U[c]; U[c]=x; D[x]=c;
  C[x]=c; S[c]++;
}
void remove(int x){
  L[R[x]]=L[x];
  R[L[x]]=R[x];
  for (int i=D[x];i!=x;i=D[i])
    for (int j=R[i];j!=i;j=R[j]){
      S[C[j]]--;
      U[D[j]]=U[j]; D[U[j]]=D[j];
    }
}
void resume(int x){
  for (int i=U[x];i!=x;i=U[i])
    for (int j=L[i];j!=i;j=L[j]){
      S[C[j]]++;
      U[D[j]]=j; D[U[j]]=j;
    }
  L[R[x]]=x;
  R[L[x]]=x;
}
void dfs(int x){ //x means dfs level
  if (R[0]==0){
    /* found a solution */
    return;
  }
  int mini=2147483647,c;
  for (int i=R[0];i!=0;i=R[i])
    if (S[i]<mini){
      mini=S[i];
      c=i;
    }
  remove(c);
  for (int i=D[c];i!=c;i=D[i]){
    for (int j=R[i];j!=i;j=R[j])
      remove(C[j]);
    dfs(x+1);
    if (/* found a solution*/)
      return;
    for (int j=L[i];j!=i;j=L[j])
      resume(C[j]);
  }
  resume(c);
}
int main()
{
  int n,m,cases,num;
  /* initialize from 1 to n*/
  num=n+1;
  for (int i=0;i<=n;i++){
    U[i]=D[i]=i;
    L[i]=i-1,R[i]=i+1;
    S[i]=0;
  }
  R[n]=0; L[0]=n;
  for (int i=0;i<m;i++){
    /* Setting the element's L and
     * R in diffierent problem
     * situations */
    insert(num,a);
    insert(num+1,b);
    L[num]=R[num]=num+1;
    L[num+1]=R[num+1]=num;
    num+=2;
  }
}
