#include <vector>
#include <algorithm>
#define N 
#define M 
#define INF 
using std::min;
using std::vector;

struct Edge{int p[2] , f[2];};

Edge base[M];
int bn; //remember to reset
vector <int> E[N];
int dist[N];
int n;
int q[N];

void bfs(int t){
  for(int i=0;i<n;++i)dist[i]=INF;
  dist[t] = 0;
  int qf = 0 , qn = 0;
  q[qn++] = t;
  while( qf < qn ){
    int now = q[qf++];
    int size = E[now].size();
    for(int i=0;i<size;++i){
      Edge *p = base+E[now][i];
      int c = (p->p[0] == now)?0:1;
      if(p->f[1-c] > 0 &&
         dist[p->p[1-c]]>
         dist[p->p[c]]+1){
        dist[p->p[1-c]]=
            dist[p->p[c]]+1;
        q[qn++] = p->p[1-c];
      }
    }
  }
}

int dfs(int now,int f,int t){
  if( now == t ) return f;
  int re = 0;
  int size = E[now].size();
  for(int i=0;i<size;++i){
    Edge *p = base+E[now][i];
    int c = (p->p[0] == now)?0:1;
    if( p->f[c] > 0 &&
       dist[p->p[1-c]]==
       dist[p->p[c]]-1){
      int tf = dfs(
          p->p[1-c],
          min(f,p->f[c]), t);
      p->f[c] -= tf;
      p->f[1-c] += tf;
      f -= tf;
      re += tf;
    }
  }
  return re;
}

int dinic(int s,int t){
  int re = 0;
  while(1){
    bfs(t);
    if( dist[s] == INF )
      return re;
    else re += dfs(s,INF,t);
  }
}
