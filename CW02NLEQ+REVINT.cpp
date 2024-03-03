/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#include <iostream>
#include <cmath>

#include "nleq.h"

double Variant7( double x )
{
  return 10 * cos(x) - 0.1 * x * x;
}

double Test( double x )
{
  return x;
}

int main( void )
{
  std::vector<std::pair<double, size_t>> ans = FindRoots(Variant7, -8, 2, 1e-6, Secant);

  for (int i = 0; i < ans.size(); i++)
    std::cout << ans[i].first << ' ' << ans[i].second << ' ' << Variant7(ans[i].first) << '\n';
 }