/* sub will iterate through
 * all the subset of sup */
int sub = sup ;
do {
  /* do something */
  sub = ((sub - 1) & sup) ;
} while(sub != sup) ;

/* comb will iterate through all
 * the subset of size k of the
 * set of size n */
int comb = (1 << k) - 1 ;
while(comb < (1 << n)) {
  /* do something */
  int x=(comb&-comb),y=comb+x;
  comb=((comb & ~y)/x >> 1)|y;
}

/* discretize */
vec.erase(unique(vec.begin(),
                 vec.end()) ,
          vec.end());

