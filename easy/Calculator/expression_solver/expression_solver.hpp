#ifndef EXPRESSION_SOLVER
#define EXPRESSION_SOLVER
#include <string>
#include <iostream>

typedef double (*FUNC)(double);


class Solver
{
    public:
    static void solve_expr(std::string& expression,const std::string& funcstr,const FUNC func );
    static void reinterpet_expr(std::string& expression,const std::string& funcstr,const double val);
    static void change_expr(std::string& expression, const std::string& funcstr,const std::string& resstr);
};


#endif //EXPRESSION_SOLVER