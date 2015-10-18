#include <cstdio>

int n, k;
bool adj[NMAX + 1][NMAX + 1];
bool vis[NMAX + 1];
int  lst[NMAX + 1];

bool f(int w){
  for(int i = 1; i <= N; i++)
    if(adj[w][i] && !vis[i]){
      vis[i] = true;
      if(lst[i] == -1 || f(lst[i])){
        lst[i] = w;
        return true;
      }
    }
  return false;
}

/////////////

scanf("%d %d", &N, &M);
for(int i = 1; i <= N; i++){
  for(int j = 1; j <= M; j++)
    adj[i][j] = false;
  lst[i] = -1;
}
while(M--){
  scanf("%d %d", &a, &b);
  adj[a][b] = true;
}
int ans = 0;
for(int i = 1; i <= N; i++){
  for(int j = 1; j <= N; j++)
    vis[j] = false;
  if(f(i)) ans++;
}
