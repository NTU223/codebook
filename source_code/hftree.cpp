struct HFTree {
  /* given a sequence ary[1...n] */
  /* query the index of k-th smallest element in ary[ql...qr] */
  /* 1-th smallest means the smallest */

  struct dat {
    int v, id;
    dat(int _v = 0, int _i = 0) : v(_v), id(_i) {}
    bool operator < (const dat &b) const { return v < b.v; }
  } ary[SIZE_N];

  int n;
  int ind[SIZE_LN][SIZE_N], cnt[SIZE_LN][SIZE_N];

  void clear(void){ n = 0; }

  void build(int _n, int _ary[]) {
    n = _n;
    for(int i = 1; i <= n; ++i) ary[i] = dat(_ary[i], i);
    std::sort(ary + 1, ary + n + 1);
    build(0, 1, n);
  }
  void build(int d, int le, int ri) {
    if(le == ri) {
      ind[d][le] = ary[le].id, cnt[d][le] = 0;
      return;
    }

    int mi = (le + ri >> 1);
    build(d + 1, le, mi);
    build(d + 1, mi + 1, ri);

    int p1 = le, p2 = mi + 1, p3 = le, sum = 0;
    for(; p3 <= ri; ++p3) {
      if(p1 == mi + 1 || (p2 <= ri && ind[d + 1][p1] > ind[d + 1][p2])) {
        ind[d][p3] = ind[d + 1][p2], cnt[d][p3] = sum;
        ++p2;
      } else {
        ind[d][p3] = ind[d + 1][p1], cnt[d][p3] = sum + 1;
        ++p1, ++sum;
      }
    }
  }

  int query(int ql, int qr, int k){ return query(0, 1, n, ql, qr, k); }
  int query(int d, int le, int ri, int ql, int qr, int k) {
    if(ql == qr) return ind[d][ql];
    int s1 = 0, s2 = cnt[d][qr];
    if(le != ql) s1 = cnt[d][ql - 1], s2 -= cnt[d][ql - 1];
    int mi = (le + ri >> 1);
    if(s2 >= k) return query(d + 1,
                             le, mi,
                             le + s1, le + s1 + s2 - 1,
                             k);
    else return query(d + 1,
                      mi + 1, ri,
                      mi - le + ql - s1 + 1, mi + qr - le - s1 - s2 + 1,
                      k - s2);
  }
};
