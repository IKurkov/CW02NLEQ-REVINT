/* Kurkov Ivan, 22.B05-MM, 03.03.2024 */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <cmath>
#include <algorithm>

#include "nleq.h"
#include "revint.h"

double (*RFList[])( double(*)(double), double&, double&, double, size_t & ) = {Bisection, Secant};
std::string RFNameList[] = {"Bisection", "Secant"};

std::string NLEQ7str = "10cos(x) - 0.1x^2";

double NLEQ7( double x )
{
  return 10 * cos(x) - 0.1 * x * x;
}

double val = 0;

double REVINT7( double x )
{
  return exp(-x) - x * x / 2;
}

double REVINT7Wrapper( double x )
{
  return REVINT7(x) - val;
}

void SolveNonlinear( void )
{
  double a = -1, b = 1, l, r, eps, root;
  size_t iter, n = 0;
  bool run = true;
  std::vector<std::pair<double, double>> segments;

  while (run)
  {
    std::cout << "Numerical solution of nonlinear equations menu [variant #7]:\n"
      << "1 - Solve new equation\n"
      << "2 - Change number of steps\n"
      << "3 - Change precision of roots\n"
      << "0 - exit\n";
    switch (_getch())
    {
    case '1':
      std::cout << "f(x) = " << NLEQ7str << '\n';
      do
      {
        std::cout << "Input [a, b]: ";
        std::cin >> a >> b;
      } while (a >= b);
    case '2':
      if (a > b)
        std::cout << "[Error]: No previous run data found!\n";
      else
      {
        std::cout << "Input number of steps: ";
        std::cin >> n;
      }
    case '3':
      if (a > b)
        std::cout << "[Error]: No previous run data found!\n";
      else
      {
        std::cout << "Input precision of roots: ";
        std::cin >> eps;
        segments = RootSep(NLEQ7, a, b, n, eps);
        std::cout << "Was founded " << segments.size() << " segments of sign changing\n";
        std::cout << '[' << std::setw(10) << "a, " << std::setw(9) << "b]";
        for (auto &name : RFNameList)
          std::cout << '|' << std::setw(46) << name;
        std::cout << '\n';
        std::cout << std::string(20, '-') << '+'
          << std::string(17, '-') << '+' << std::string(12, '-') << '+' << std::string(12, '-') << '+' << std::string(2, '-') << '+'
          << std::string(17, '-') << '+' << std::string(12, '-') << '+' << std::string(12, '-') << '+' << std::string(2, '-') << '\n';
        for (auto &sgm : segments)
        {
          std::cout << '[' << std::setw(8) << sgm.first << ", " << std::setw(8) << sgm.second << "]";
          for (auto find : RFList)
          {
            root = find(NLEQ7, l = sgm.first, r = sgm.second, eps, iter);
            std::cout << '|' << std::setw(17) << std::setprecision(15) << root
                      << '|' << std::setw(12) << std::setprecision(7) << fabs(r - l)
                      << '|' << std::setw(12) << fabs(NLEQ7(root))
                      << '|' << std::setw(2) << iter;
          }
          std::cout << '\n';
        }
      }
      break;
    case '0':
      run = false;
      break;
    default:
      std::cout << "[Error]: Incorrect choice!\n";
    }
  }
}

void PrintValues( const double *nodes, const double *values, size_t size )
{
  std::cout << std::setw(18) << "f(x)" << '|' << std::setw(18) << 'x' << '\n'
    << std::string(18, '-') << '+' << std::string(18, '-') << '\n';
  for (size_t i = 0; i < size; i++)
    std::cout << std::setw(18) << nodes[i] << '|' << std::setw(18) << values[i] << '\n';
}

void SolveReverseInterpolation( void )
{
  bool run = true;
  size_t n, m, start, iter;
  double a = -1, b = 1, x, e = 0, *nodes = nullptr, *values = nullptr;
  std::vector<std::pair<double, double>> segments;

  while (run)
  {
    std::cout << "Reverse interpolation problem menu [variant #7]:\n"
      << "1 - Solve new interpolation problem\n"
      << "0 - exit\n";
    switch (_getch())
    {
    case '1':
      std::cout << "Input number of arguments: ";
      std::cin >> m;
      do
      {
        std::cout << "Input [a, b]: ";
        std::cin >> a >> b;
      } while (a >= b);

      if (a > b)
      {
        delete[] nodes;
        delete[] values;
      }
      nodes = new double[m];
      values = new double[m];
      GenNodes(nodes, m, a, b);
      GenValues(nodes, values, m, REVINT7);
      PrintValues(values, nodes, m);

      std::cout << "Input value: ";
      std::cin >> val;
      do
      {
        std::cout << "Input degree of Lagrange polynomial for f^{-1} < " << m << ": ";
        std::cin >> n;
      } while (n >= m);

      start = FindNClosest(values, m, val, n + 1);
      x = LagrangeInterpolation(values + start, nodes + start, n + 1, val);
      PrintValues(values + start, nodes + start, n + 1);
      std::cout << "f^{-1}(" << val << ") = " << std::setprecision(15) << x << '\n'
                << "|f(" << x << ") - " << val << "| = " << fabs(val - REVINT7(x)) << '\n';

      do
      {
        std::cout << "Input degree of Lagrange polynomial for f < " << m << ": ";
        std::cin >> n;
      } while (n >= m);
      std::cout << "Input precision of roots: ";
      std::cin >> e;
      segments = RootSep(REVINT7Wrapper, a, b, n, e);
      for (auto &sgm : segments)
      {
        x = Secant(REVINT7Wrapper, sgm.first, sgm.second, e, iter);
        std::cout << "f^{-1}(" << val << ") = " << x << '\n'
          << "|f(" << x << ") - " << val << "| = " << fabs(val - REVINT7(x)) << '\n';
      }
      break;
    case '0':
      run = false;
      delete[] nodes;
      delete[] values;
      break;
    default:
      std::cout << "[Error]: Incorrect choice!\n";
    }
  }
}

int main( void )
{
  int key;

  std::cout << "Please choose what to solve:\n"
            << "n - nonlinear equation\n"
            << "r - reverse interpolation problem\n";
  while ((key = _getch()) != 'n' && key != 'N' && key != 'r' && key != 'R')
    std::cout << "Incorrect choice!\n";
  if (key == 'n' || key == 'N')
  {
    SolveNonlinear();
  }
  else if (key == 'r' || key == 'R')
  {
    SolveReverseInterpolation();
  }
  return 0;
}