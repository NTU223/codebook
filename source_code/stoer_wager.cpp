#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int SIZE_N = (150 + 10);
const int INF = (1000000000);

int T, n, m;
int edg[SIZE_N][SIZE_N];

int nod[SIZE_N], dis[SIZE_N],
    use[SIZE_N];

int SW(void) {
  int V = n, cut = INF;
  for(int i = 0; i <= V; ++i)
    nod[i] = i;
  while(V > 1) {
    dis[nod[1]] = 0;
    use[nod[1]] = 1;
    for(int i=2; i<=V; ++i) {
      dis[nod[i]] = 0;
      use[nod[i]] = 0;
    }

    int las = 1;
    for(int cnt=2;cnt<=V;++cnt){
      for(int i=1; i<=V; ++i) {
        if(use[nod[i]] == 1)
          continue;
        dis[nod[i]] +=
            edg[nod[las]][nod[i]];
      }

      int max = -1, now = 0;
      for(int i=1; i<=V; ++i){
        if(use[nod[i]] == 1)
          continue;
        if(dis[nod[i]] > max)
          max=dis[nod[i]], now=i;
      }

      if(cnt == V) {
        for(int i=1; i<=V; ++i) {
          edg[nod[i]][nod[las]]+=
              edg[nod[i]][nod[now]];
          edg[nod[las]][nod[i]]=
              edg[nod[i]][nod[las]];
        }
        cut=min(cut,dis[nod[now]]);
        swap(nod[now], nod[V]);
        --V;
      } else {
        las = now;
        use[nod[las]] = 1;
      }
    }
  }
  return cut;
}
int main(void) {
  scanf("%d%d", &n, &m);
  for(int i=0,a,b,c;i<m;++i){
    scanf("%d%d%d",&a,&b,&c);
    edg[a][b]+=c;
    edg[b][a]+=c;
  }

  printf("%d\n", SW());

  clear();
  return 0;
}

