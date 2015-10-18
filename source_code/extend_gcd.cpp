void extGCD(int a, int b, int& t1, int& t2, int& g){
  if(b == 0){ g = a; t1 = 1; t2 = 0; }
  else{
    extGCD(b, a%b, t1, t2, g);
    int tmp = t1;
    /* g = a*t1 + b*t2  */
    t1 = t2; t2 = tmp - (a/b)*t2;
    /* g = a*t1 - b*t2 */
    // t1 = -t2; t2 = -tmp - (a/b)*t2;
  }
}
