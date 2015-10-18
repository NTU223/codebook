struct Treap{
  Treap *l, *r;
  int pri, key;
  Treap(){};
  Treap( int _key ) :
      l(NULL), r(NULL),
      pri(rand()), key(_key){}
};
Treap* merge(Treap*a,Treap*b){
  if(!a || !b ) return a?a:b;
  if( a->pri > b->pri ){
    a->r = merge( a->r, b );
    return a;
  } else {
    b->l = merge( a, b->l );	
    return b;
  }
}
/* split t into two parts,
 * part a with elements <= k,
 * part b with elements > k*/
void split(Treap*t,int k,Treap*&a,
           Treap *&b) {
  if( !t ) a = b = NULL;
  else if( t->key <= k ){
    a = t;
    split( t->r, k, a->r, b );
  } else {
    b = t;
    split( t->l, k, a, b->l);		
  }
}
Treap* insert(Treap *t, int k){
  Treap *a, *b;
  split( t, k, a, b);
  return merge(merge(
          a, new Treap(k)), b);
}
Treap remove(Treap *t, int k){
  Treap *a, *b, *c;
  split(t, k-1, a, b);
  split(b, k, b, c);	
  return merge(a, c);
}
