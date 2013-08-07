/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Soonho Kong
*/
#include <cmath>
#include "mpfp.h"

namespace lean {

// mpq & mpq::operator=(mpbq const & b) {
//     *this = 2;
//     power(*this, *this, b.get_k());
//     inv();
//     *this *= b.get_numerator();
//     return *this;
// }

// int cmp(mpq const & a, mpz const & b) {
//     if (a.is_integer()) {
//         return mpz_cmp(mpq_numref(a.m_val), mpq::zval(b));
//     }
//     else {
//         static thread_local mpz tmp;
//         mpz_mul(mpq::zval(tmp), mpq_denref(a.m_val), mpq::zval(b));
//         return mpz_cmp(mpq_numref(a.m_val), mpq::zval(tmp));
//     }
// }

// void mpq::floor() {
//     if (is_integer())
//         return;
//     bool neg = is_neg();
//     mpz_tdiv_q(mpq_numref(m_val), mpq_numref(m_val), mpq_denref(m_val));
//     mpz_set_ui(mpq_denref(m_val), 1);
//     if (neg)
//         mpz_sub_ui(mpq_numref(m_val), mpq_numref(m_val), 1);
// }

// void mpq::ceil() {
//     if (is_integer())
//         return;
//     bool pos = is_pos();
//     mpz_tdiv_q(mpq_numref(m_val), mpq_numref(m_val), mpq_denref(m_val));
//     mpz_set_ui(mpq_denref(m_val), 1);
//     if (pos)
//         mpz_add_ui(mpq_numref(m_val), mpq_numref(m_val), 1);
// }

// mpz floor(mpq const & a) {
//     if (a.is_integer())
//         return a.get_numerator();
//     mpz r;
//     mpz_tdiv_q(mpq::zval(r), mpq_numref(a.m_val), mpq_denref(a.m_val));
//     if (a.is_neg())
//         --r;
//     return r;
// }

// mpz ceil(mpq const & a) {
//     if (a.is_integer())
//         return a.get_numerator();
//     mpz r;
//     mpz_tdiv_q(mpq::zval(r), mpq_numref(a.m_val), mpq_denref(a.m_val));
//     if (a.is_pos())
//         ++r;
//     return r;
// }

// void power(mpq & a, mpq const & b, unsigned k) {
//     mpz_pow_ui(mpq_numref(a.m_val), mpq_numref(b.m_val), k);
//     mpz_pow_ui(mpq_denref(a.m_val), mpq_denref(b.m_val), k);
//     mpq_canonicalize(a.m_val);
// }

// extern void display(std::ostream & out, __mpz_struct const * v);

inline unsigned necessary_digits(mpfr_prec_t p) {
    static constexpr double LOG10_2 = 0.30102999566;
    return std::ceil(p * LOG10_2) + 2;
}

std::ostream & operator<<(std::ostream & out, mpfp const & v) {
    static thread_local char* s = nullptr;
    static thread_local char format[128];
    sprintf(format, "%%.%dRNg", necessary_digits(mpfr_get_prec(v.m_val)));
    mpfr_asprintf(&s, format, v.m_val);
    std::string str = std::string(s);
    out << str;
    return out;
}
// void display_decimal(std::ostream & out, mpq const & a, unsigned prec) {
//     mpz n1, d1, v1;
//     numerator(n1, a);
//     denominator(d1, a);
//     if (a.is_neg()) {
//         out << "-";
//         neg(n1);
//     }
//     v1 = n1 / d1;
//     out << v1;
//     n1 = rem(n1, d1);
//     if (n1.is_zero())
//         return;
//     out << ".";
//     for (unsigned i = 0; i < prec; i++) {
//         n1 *= 10;
//         v1 = n1 / d1;
//         lean_assert(v1 < 10);
//         out << v1;
//         n1 = rem(n1, d1);
//         if (n1.is_zero())
//             return;
//     }
//     out << "?";
// }

}

// void print(lean::mpq const & v) { std::cout << v << std::endl; }
