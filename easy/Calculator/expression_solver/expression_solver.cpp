#include "expression_solver.hpp"

void Solver::solve_expr(std::string& expression,const std::string& funcstr,const FUNC func ) 
    {
        int a = expression.find(funcstr);
        while (a!=-1)
        {
            int b = a +funcstr.length() +expression.substr(a+funcstr.length()).find(")");
            // std::cout << "ERASING FROM " << a << " TO " << b << std::endl;
            if (b < a) 
            {
                throw std::runtime_error("Unmatched parentheses");
            }
            std::string trigexpr = expression.substr(a+funcstr.length(),b-a-funcstr.length());
            expression.erase(expression.begin()+a, expression.begin()+b+1);
            std::string evaluated = std::to_string(func(std::stod(trigexpr)));
            int trlen = evaluated.length();
            for (int i = 0; i!=trlen; i++){
                expression.insert(expression.begin()+a+i,evaluated[i]);
            }
            a = expression.find(funcstr);
            std::cout << expression << "   {\"" << funcstr << trigexpr << ")\" resolved}\n";
        }
        
    }   

void Solver::reinterpet_expr(std::string& expression,const std::string& funcstr,const double val)
{
    int a = expression.find(funcstr);
    std::cout << "EXPRESSION: " << a << "\n";
    while (a!=-1)
    {
        int b = a +funcstr.length();
        std::string trigexpr = std::to_string (val);
        int trlen = trigexpr.length();
        expression.erase(expression.begin()+a, expression.begin()+b);
        expression.insert(expression.begin()+a,trigexpr.begin(),trigexpr.end());
        
        std::cout << expression << "   {\"" << funcstr << "\" reinterpreted}\n";
        a = expression.find(funcstr);
    }
    
}

void Solver::change_expr(std::string& expression, const std::string& funcstr,const std::string& resstr)
{
    int a = expression.find(funcstr);
    while (a!=-1)
    {
        int b = a +funcstr.length();

        int trlen = resstr.length();
        expression.erase(expression.begin()+a, expression.begin()+b);
        for (int i = 0; i!=trlen; i++)
        {
            expression.insert(expression.begin()+a+i,resstr[i]);
        }
        std::cout << expression << "   {\"" << funcstr << "\" changed}\n";
        a = expression.find(funcstr);
    }
}

