/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#ifndef NLEQ_H
#define NLEQ_H

#include <vector>

double Bisection( double (*f)(double), double &left, double &right, double eps, size_t &iter );
double Secant( double (*f)(double), double &prev, double &cur, double eps, size_t &iter );
std::vector<std::pair<double, double>> RootSep( double (*f)(double), double left, double right, size_t N, double eps );

#endif // !NLEQ_H