// g++ validate.cc -lgmp -lgmpxx -O3 -Wall -pedantic -Wextra -o validate
// (cpplinted and cppchecked)
//
#include <gmpxx.h>
#include <assert.h>

#include <iostream>
#include <iomanip>

const int siz = 10000000;
char *buf = new char[siz];

mpz_class C[6][5];

mpz_class val(char *buf) {
    char *q = buf + strlen(buf) - 1;
    while (!isxdigit(*q)) *q--='\0';
    return mpz_class(buf);
}

void read_C() {
    FILE *src = fopen("Colbert.py", "r");

    buf = fgets(buf, siz, src);
    for (int i = 0; i < 6; ++i) {
       buf = fgets(buf, siz, src);
       for (int j = 0; j < 5; ++j) {
         buf = fgets(buf, siz, src);
         C[i][j] = val(buf);
       }
       buf = fgets(buf, siz, src);
    }
    fclose(src);
}

int main() {
    mpz_class sq = 0, two = 2, p;
    assert(buf);

    read_C();

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
