/**********************************************/
/* [usage]: kmp(str1, str2)                   */
/* [check]: return true if str1 contains str2 */
/**********************************************/
#include<string.h>
int kmp_fail[maxn];
bool kmp(char* s, char* t){
  int s_len = strlen(s), t_len = strlen(t);
  int tmp, s_pos, t_pos;
  kmp_fail[0] = -1;
  for(int i=1; i<t_len; i++){
    tmp = kmp_fail[i-1];
    while( t[i] != t[tmp+1] && tmp!=-1) tmp = kmp_fail[tmp];
    if(t[i] == t[tmp+1]) kmp_fail[i] = tmp+1;
    else kmp_fail[i] = -1;
  }
  s_pos = t_pos = 0;
  while(s_pos < s_len){
    if(s[s_pos] == t[t_pos]){
      s_pos++; t_pos++;
      if(t_pos == t_len) return true;
    }
    else if(t_pos == 0) s_pos++;
    else t_pos = kmp_fail[t_pos-1] + 1;
  }
  return false;
}
