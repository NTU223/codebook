Vst[Now] = true;
Low[now] = Dfn[Now];
count = 0;
isAP = false;
for (Vertex p : neighbor(Now)) {
  if (Vst[p] == true && p != PreV)
    Low[Now] = min(Low[Now], Dfn[p]);
  if (Vst[p] == false) {
    count = count + 1;
    Dfn[p] = Dfn[Now] + 1;
    DFS(Now, p, Vst, Dfn, Low, AP);
    if (DFn[Now] >= Low[p])
      isAP = true;
    Low[Now] = Min(Low[Now], Low[p]);
  }
}
if ((Dfn[Now] == 0 && count > 1) || isAP)
  AP.push_back(Now);
