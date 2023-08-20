#include <gmpxx.h>
#include <assert.h>

#include <iostream>
#include <iomanip>

const int siz = 10000000;
char *buf = new char[siz];

mpz_class C[6][5] =
#include "Colbert.h"

int main() {
    mpz_class sq = 0, two = 2, p;
    assert(buf);

    std::cout << "6 entries of the form [k,n,s,x,y], with p=k*2^n+1, "
              << "s^2%p==p-1 and p==x^2+y^2\n";

    for (int i = 0; i < 6; ++i) {
        std::ostringstream oss;
        mpz_ui_pow_ui(p.get_mpz_t(), 2, C[i][1].get_ui()); p *= C[i][0]; p += 1;
        oss << C[i][0] << "*2^" << C[i][1] << "+1";
        std::cout
            << std::right << std::setw(18) << oss.str() << " ("
            << strlen(mpz_get_str(buf, 10, p.get_mpz_t())) << "-digit prime)\n";

        mpz_powm(sq.get_mpz_t(),
                 C[i][2].get_mpz_t(), two.get_mpz_t(), p.get_mpz_t());
        assert(sq == p-1);

        assert(C[i][3]*C[i][3] + C[i][4]*C[i][4] == p);
    }

    std::cout << "done, all asserts OK\n";
    delete buf;

    return 0;
}
