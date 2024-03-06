/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#ifndef REVINT_H
#define REVINT_H

void GenNodes( double *nodes, size_t size, double left, double right );
void GenValues( const double *nodes, double *values, size_t size, double (*f)(double) );
size_t FindNClosest( const double *nodes, size_t size, double target, size_t n );
double LagrangeInterpolation( const double *nodes, const double *values, size_t deg, double x );

#endif // !REVINT_H

