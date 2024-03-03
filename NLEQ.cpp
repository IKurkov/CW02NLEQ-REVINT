/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#include <vector>
#include <cmath>

#include "nleq.h"

double Bisection( double (*f)(double), double left, double right, double eps, size_t &iter )
{
  double middle;

  iter = 0;
  while (fabs(right - left) >= 2 * eps)
  {
    middle = (right + left) / 2;
    if (f(left) * f(middle) <= 0)
      right = middle;
    else
      left = middle;
    iter++;
  }
  return right;
}

double Secant( double (*f)(double), double prev, double cur, double eps, size_t &iter )
{
  double next;

  iter = 0;
  while (fabs(cur - prev) >= eps)
  {
    next = cur - f(cur) / (f(cur) - f(prev)) * (cur - prev);
    prev = cur;
    cur = next;
    iter++;
  }
  return cur;
}

std::vector<std::pair<double, double>> RootSep( double (*f)(double), double left, double right, double eps )
{
  std::vector<std::pair<double, double>> segments;
  size_t N = right - left >= 1 ? 2 * (size_t)(right - left) : 2, sign_change;
  double h = (right - left) / N, a, b;

  do
  {
    sign_change = segments.size();
    segments.clear();
    a = left;
    b = a + h;
    for (size_t i = 0; i < N; i++)
    {
      if (f(a) * f(b) < 0)
        segments.push_back({a, b});
      if (f(a) == 0)
        segments.push_back({a - h, a + h});
      a += h;
      b += h;
    }
    if (f(a) == 0)
      segments.push_back({a - h, a + h});
    h /= 2;
    N *= 2;
  } while (h > 2 * eps && segments.size() > sign_change);
  return segments;
}

std::vector<std::pair<double, size_t>>
  FindRoots( double (*f)(double), double left, double right, double eps, method_t find )
{
  std::vector<std::pair<double, size_t>> roots;
  std::vector<std::pair<double, double>> segments = RootSep(f, left, right, eps);
  size_t iter;

  for (auto &s: segments)
    roots.push_back(std::make_pair(find(f, s.first, s.second, eps, iter), iter));
  return roots;
}