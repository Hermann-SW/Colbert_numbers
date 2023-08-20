# pylint: disable=C0103
#                 invalid-name
"""
pylint-ed and black-ed
"""
from math import ceil
from gmpy2 import mpz, log10  # pylint: disable=no-name-in-module
from Colbert import C

print("6 entries of the form [k,n,s,x,y], with p=k*2**n+1, s**2%p==p-1 and p==x**2+y**2")
p = C[0][0] * 2 ** C[0][1] + 1
for v in C:
    p = mpz(v[0]) * 2 ** mpz(v[1]) + 1
    print(
        (str(v[0]) + "*2**" + str(v[1]) + "+1").rjust(20),
        "(" f"{int(ceil(log10(p))):d}" "-digit prime)",
    )
    assert pow(mpz(v[2]), 2, p) == p - 1
    assert mpz(v[3]) ** 2 + mpz(v[4]) ** 2 == p

print("done, all asserts OK")
