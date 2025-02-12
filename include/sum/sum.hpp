#ifndef SUM_SUM_HPP
#define SUM_SUM_HPP

#include <vector>

double sum(const std::vector<double>& inp);

/** Computes a sum of numbers using vectorization of 2 */
double sum_vectorize2(const std::vector<double>& inp);
/** Computes a sum of numbers using vectorization of 4 */
double sum_vectorize4(const std::vector<double>& inp);
/** Computes a sum of numbers using vectorization of 8 */
double sum_vectorize8(const std::vector<double>& inp);
/** Computes a sum of numbers using vectorization of 16 */
double sum_vectorize16(const std::vector<double>& inp);
/** Computes a sum of numbers using vectorization of 16/8/4/2 */
double sum_vectorize(const std::vector<double>& inp);

/** Computes a sum of numbers using Kahan algorithm */
double sum_kahan(const std::vector<double>& inp);

/** Computes a sum of numbers using Kahan algorithm over long double */
double sum_kahan_long(const std::vector<double>& inp);

/** Computes a sum of numbers using Kahan algorithm with vectorization of 4 */
double sum_kahan_vec4(const std::vector<double>& inp);
/** Computes a sum of numbers using Kahan algorithm with vectorization of 8 */
double sum_kahan_vec8(const std::vector<double>& inp);
/** Computes a sum of numbers using Kahan algorithm with vectorization of 16 */
double sum_kahan_vec16(const std::vector<double>& inp);

#endif  // SUM_SUM_HPP
