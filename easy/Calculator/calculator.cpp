#include <iostream>
#include <cmath>

#include "shunting_yard/shunting_yard.hpp"
#include "expression_solver/expression_solver.hpp"

double cot (double X){return 1/std::tan(X);}


int main(int argc, char** argv)
{
    
    const double pi = 3.14159265358979323846;
    const double e = std::exp(1.0);
    std::string a = "1+sin(123)-cos(12)+tan(2) + log2(4)         - e";
    Solver::solve_expr(a, "sin(", std::sin);
    Solver::solve_expr(a, "cos(", std::cos);
    Solver::solve_expr(a, "tan(", std::tan);
    Solver::solve_expr(a, "cot(", cot);
    Solver::solve_expr(a, "ln(", std::log);
    Solver::solve_expr(a, "log10(", std::log10);
    Solver::solve_expr(a, "log2(", std::log2);
    Solver::reinterpet_expr(a, "pi", pi);
    Solver::reinterpet_expr(a, "e", e);
    Solver::change_expr(a, "+-", "-");

    Solver::change_expr(a, " ", "");
    std::cout << a << "\n";
    return 0;
}