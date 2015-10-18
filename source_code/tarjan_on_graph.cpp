/****************************************/
/*  Tarjan's algorithm                  */
/*  Find articulation points, bridges,  */
/*      BCC, SCC, and solve 2-SAT       */
/****************************************/

#include <stdio.h>
#include <stack>
#include <vector>
#include <utility>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define V 1000007
#define E 1000007

using namespace std;

typedef pair<int, int> pii;

vector<pii> edge[V];    // adjacent list
// first: destination, second: edge index
stack<int> stk;         // stack for BCC/SCC
int time, new_id;       // global counters
int stamp[V];           // timestamp (use global "time")
int low[V];             // low function
bool instack[V];        // only needed in SCC
bool is_articulation[V];// articulation point result
bool is_bridge[E];      // bridge result
int contract[V];        // contracted point id (use global "new_id")
vector<int> group[V];   // SCC groups

vector<pair<int, int> > edge_arr;

void add_edge(int st, int ed, int edge_idx = 0){
  edge[st].push_back(make_pair(ed, edge_idx));
}

void dfs(int now, int par){
  stamp[now] = low[now] = time++;
  stk.push(now);
  instack[now] = true;
  bool flg = false;
  int child_cnt = 0;
  for(unsigned i=0, n=edge[now].size(); i<n; ++i){
    int nxt = edge[now][i].first;
    int edge_idx = edge[now][i].second;
    // [Important] don't need this "if" in SCC/2-SAT
    if(nxt != par){
      // tree edge
      if(stamp[nxt] == -1){
        child_cnt++;
        dfs(nxt, now);
        low[now] = min(low[now], low[nxt]);
        if(low[nxt] >= stamp[now]) flg = true;
        if(low[nxt] > stamp[now]) is_bridge[edge_idx] = true;
      }
      // back edge in BCC, always true (can change to "else")
      // back / forward / cross edge in SCC
      else if(instack[nxt])
        low[now] = min(low[now], stamp[nxt]);
    }
  }
  if( (now == par && child_cnt >= 2) ||
     (now != par && flg)) is_articulation[now] = true;
  if(low[now] == stamp[now]){
    int v;
    do{
      v = stk.top(); stk.pop();
      instack[v] = false;
      contract[v] = new_id;
      group[new_id].push_back(v);
    } while(v != now);
    new_id++;
  }
}

// if don't need bridges, use tarjan(v)
void tarjan(int v, int e = 0){
  time = 0;
  new_id = 0;
  while(!stk.empty()) stk.pop();
  for(int i=0; i<v; ++i) stamp[i] = -1;
  for(int i=0; i<v; ++i) instack[i] = false;
  for(int i=0; i<v; ++i) is_articulation[i] = false;
  for(int i=0; i<e; ++i) is_bridge[i] = false;
  for(int i=0; i<v; ++i) group[i].clear();
  for(int i=0; i<v; ++i)
    if(stamp[i] == -1)
      dfs(i, i);
}

/**** 2-SAT part  ***/
// lit = var*2 (positive), var*2+1 (negative)
#define inv(x) ((x)^1)
vector<int> order;      // reversed topological order, only needed in 2-SAT
bool visit[V];          // visit tag
int scc_assignment[V];  // assignments for SCC groups
int var_assignment[V];  // assignments for variables

void toposort(int now){
  if(visit[now]) return;
  visit[now] = true;
  for(int i=0, n=group[now].size(); i<n; ++i){
    int node = group[now][i];
    for(int j=0, m=edge[node].size(); j<m; ++j){
      int nxt = edge[node][j].first;
      toposort(contract[nxt]);
    }
  }
  for(int i=0, n=group[now].size(); i<n; ++i)
    order.push_back(group[now][i]);
}

bool two_sat(int nVar){
  tarjan(nVar*2);
  // check SAT
  for(int i=0; i<nVar; ++i)
    if(contract[2*i] == contract[2*i+1])
      return false;
  // topological order
  order.clear();
  for(int i=0; i<new_id; ++i) visit[i] = false;
  for(int i=0; i<new_id; ++i)
    if(!visit[i])
      toposort(i);
  // initialize assignment
  for(int i=0; i<new_id; ++i) scc_assignment[i] = -1;
  // SCC assignment
  for(int i=0; i<2*nVar; ++i){
    int lit = order[i];
    if(scc_assignment[contract[lit]] == -1){
      scc_assignment[contract[lit]] = 1;
      scc_assignment[contract[inv(lit)]] = 0;
    }
  }
  // variable assignment
  for(int i=0; i<nVar; ++i)
    var_assignment[i] = scc_assignment[contract[2*i]];
  return true;
}
