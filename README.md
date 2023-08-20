A Colbert number (https://oeis.org/A258074) is an integer with more than 1,000,000 digits that is prime and has contributed to the in-progress computational proof that 78557 is the smallest Sierpiński number. 

[Colbert.py](Colbert.py) contains entries [k,n,s,x,y] for the 6 Colbert numbers. Because the numbers are huge, that file is 35MB in size. For Colbert prime *p=k\*2^n+1*, *s^2 % p == p-1* and *p == x^2 + y^2*.  
[After having computed *sqrt(-1) (mod p)* for biggest 9,383,761-digit Colbert number in 10:45:01h [with patched LLR software](https://github.com/Hermann-SW/9383761-digit-prime#fast-sqrt-1-mod-p-for-9383761-digit-prime-p-1-mod-4), the other numbers were processed as well. Sum of suqares was easy to determine in few seconds from *sqrtm1 = sqrt(-1) (mod p)* with PARI/GP "halfgcd(sqrtm1, p)"]

The huge numbers had to be stored as hex numbers because of Python runtime performance only.

File extension is ".py" so that Python can import it, but it can be read from PARI/GP with "\r Colbert.py" as well.

Since libgmpxx "mpz_class(...)" is not part of Colbert.py, Colbert.h needs to be created from Colbert.py for C++.

Same validation done in three languages, shortest PARI/GP script [validate.gp](validate.gp):
```
\r Colbert.py
assert(b) = { if(!(b), error("assertion failed")); }
print("6 entries of the form [k,n,s,x,y], with p=k*2^n+1, s^2%p==p-1 and p==x^2+y^2");
foreach(C,v,p=v[1]*2^v[2]+1;\
  printf("%18s (%d-digit prime)\n",Str(v[1],"*2^",v[2],"+1"),#digits(p));\
  assert(v[3]^2%p==p-1);\
  assert(v[4]^2+v[5]^2==p);\
);
print("done, all asserts OK");
```

Here is validation done for all three languages ([Makefile](Nakefile) has ```lint``` and ```clean``` targets in addition):  
```
hermann@7600x:~/Colbert_numbers$ make
sed "s/C =//;\
     y/[]/{}/;\
     s/\([0-9a-fx][0-9a-fx]*\)/mpz_class\(\"\1\"\)/g;" Colbert.py > Colbert.h
g++ validate.cc -lgmp -lgmpxx -O3 -Wall -pedantic -Wextra -o validate

time -f %E\\n  gp -q < validate.gp
6 entries of the form [k,n,s,x,y], with p=k*2^n+1, s^2%p==p-1 and p==x^2+y^2
  5359*2^5054502+1 (1521561-digit prime)
 33661*2^7031232+1 (2116617-digit prime)
 28433*2^7830457+1 (2357207-digit prime)
 27653*2^9167433+1 (2759677-digit prime)
19249*2^13018586+1 (3918990-digit prime)
10223*2^31172165+1 (9383761-digit prime)
done, all asserts OK
0:04.25

time -f %E\\n  ./validate
6 entries of the form [k,n,s,x,y], with p=k*2^n+1, s^2%p==p-1 and p==x^2+y^2
  5359*2^5054502+1 (1521561-digit prime)
 33661*2^7031232+1 (2116617-digit prime)
 28433*2^7830457+1 (2357207-digit prime)
 27653*2^9167433+1 (2759677-digit prime)
19249*2^13018586+1 (3918990-digit prime)
10223*2^31172165+1 (9383761-digit prime)
done, all asserts OK
0:03.90

time -f %E\\n  python validate.py
6 entries of the form [k,n,s,x,y], with p=k*2**n+1, s**2%p==p-1 and p==x**2+y**2
   5359*2**5054502+1 (1521561-digit prime)
  33661*2**7031232+1 (2116617-digit prime)
  28433*2**7830457+1 (2357207-digit prime)
  27653*2**9167433+1 (2759677-digit prime)
 19249*2**13018586+1 (3918990-digit prime)
 10223*2**31172165+1 (9383761-digit prime)
done, all asserts OK
0:02.71

hermann@7600x:~/Colbert_numbers$ 
```
