/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#ifndef NLEQ_H
#define NLEQ_H

using method_t = double( double(*)(double), double, double, double, size_t& );

double Bisection( double (*f)(double), double left, double right, double eps, size_t &iter );
double Secant( double (*f)(double), double prev, double cur, double eps, size_t &iter );
std::vector<std::pair<double, double>> RootSep( double (*f)(double), double left, double right, double eps );
std::vector<std::pair<double, size_t>>
  FindRoots( double (*f)(double), double left, double right, double eps, method_t find );

#endif // !NLEQ_H