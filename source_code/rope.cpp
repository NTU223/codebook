#include <algorithm>
#include <ext/rope>

typedef __gnu_cxx::rope<char> crop;

crop str[SIZE_N];

int main(void) {
  for(int count=1;
      scanf("%d",&n)!=EOF;
      ++count, clear()) {
    int ver = 0, cnt = 0;
    for(int i = 0; i < n; ++i) {
      int t, v, p, c;
      scanf("%d", &t);
      if(t == 1) {
        scanf("%d", &p);
        scanf("%s", temp);
        ++ver, p -= cnt;
        crop t(temp);
        str[ver] = str[ver - 1];
        str[ver].insert(p, t);
      } else if(t == 2) {
        scanf("%d%d", &p, &c);
        ++ver;
        p -= cnt;
        c -= cnt;
        str[ver] = str[ver-1];
        str[ver].erase(p-1,c);
      } else if(t == 3) {
        scanf("%d%d%d",&v,&p,&c);
        v -= cnt;
        p -= cnt;
        c -= cnt;
        for(int j=p-1, jl=p+c-1;
            j<jl; ++j) {
          char c = str[v][j];
          printf("%c", c);
          if(c == 'c') ++cnt;
        }
        puts("");
      }
    }
  }
}

