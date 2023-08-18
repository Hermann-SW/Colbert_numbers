\r Colbert.py
assert(b) = { if(!(b), error("assertion failed")); }
print("6 entries of the form [k,n,s,x,y], with p=k*2^n+1, s^2%p==p-1 and p==x^2+y^2");
foreach(C,v,p=v[1]*2^v[2]+1;\
  printf("%18s (%d-digit prime)\n",Str(v[1],"*2^",v[2],"+1"),#digits(p));\
  assert(v[3]^2%p==p-1);\
  assert(v[4]^2+v[5]^2==p);\
);
print("done, all asserts OK");
