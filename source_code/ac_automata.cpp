/////////////////////////////////////////
// [usg] init()->add()*n->link()->match()
//       remember to free() in the end!!
// [chk] str[i] is matched if ( occ[i] ||
//      ( equ[i] != -1 && occ[equ[i]] ) )
/////////////////////////////////////////

#include<stdio.h>
#include<string.h>

// # of characters
// need to map all characters to 0~(C-1)
#define C 53

struct NODE{
  NODE *next[C], *fail, *rec;
  int ind;
  NODE(){
    for(int i=0; i<C; i++)
      next[i] = NULL;
    fail = rec = NULL;
    ind = -1;
  }
}*root;
bool occ[1001]; // yes or no
int equ[1001];  // repeated strings
void init(){
  for(int i=0; i<C; i++) {
    occ[i] = false; equ[i] = -1;
  }
  root = new NODE;
}
void free(NODE *p = root){
  for(int i=0; i<C; i++){
    if(p->next[i] != NULL)
      free(p->next[i]);
  }
  delete p;
}
void add(char *s, int mrk){
  int len=strlen(s);
  NODE *p = root;
  for(int i=0; i<len; i++){
    if(p->next[s[i]] == NULL)
      p->next[s[i]] = new NODE;
    p = p->next[s[i]];
  }
  if(p->ind == -1) p->ind = mrk;
  else equ[mrk] = p->ind;
}
void link(NODE *p = root){
  NODE *tmp;
  for(int i=0; i<C; i++){
    if(p->next[i] == NULL) continue;
    tmp = p->fail;
    while(tmp != NULL &&
          tmp->next[i] == NULL)
      tmp = tmp->fail;
    if(tmp != NULL)
      p->next[i]->fail = tmp->next[i];
    else p->next[i]->fail = root;
    if(p->next[i]->fail->ind != -1)
      p->rec = p->next[i]->fail;
    else p->rec = p->next[i]->fail->rec;
  }
  for(int i=0; i<C; i++){
    if(p->next[i] != NULL)
      link(p->next[i]);
  }
}
void match(char *s){
  NODE *p = root;
  int len = strlen(s);
  NODE* tmp;
  for(int i=0; i<len; i++){
    while(p != NULL &&
          p->next[s[i]] == NULL)
      p = p->fail;
    if(p != NULL) p = p->next[s[i]];
    else p = root;
    tmp = p;
    while(tmp != NULL){
      if(tmp->ind != -1)
        occ[tmp->ind] = true;
      tmp = tmp->rec;
    }
  }
}
