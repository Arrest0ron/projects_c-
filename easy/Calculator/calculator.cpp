#include <iostream>
#include <cmath>
#include <vector>

#include "shunting_yard/shunting_yard.hpp"
#include "expression_solver/expression_solver.hpp"

double cot (double X){return 1/std::tan(X);}
bool isoperator(char s);
std::vector<std::string> tokenize(std::string& equation);



FuncDef _cos{std::cos, "cos("};



int main(int argc, char** argv)
{
    
    const double pi = 3.14159265358979323846;
    const double e = std::exp(1.0);
    std::string a = "3 * ( 5 + (67 * 732 )+ cos(cos(2))  )";
    std::vector<std::string> tokens = tokenize(a);
    for (std::string& j : tokens)
    {
        if (isdigit(j[0])){continue;}
        // Solver::solve_expr(j,"cos(", std::cos);
        // Solver::reinterpet_expr(j,"pi", pi);
        // Solver::reinterpet_expr(j,"e", e);
        // Solver::solve_expr(j,_cos.name,_cos.p);
    }
    

    for (auto i : tokens)
    {
        std::cout <<  i << "\n";
    }
    return 0;
}

std::vector<std::string> tokenize(std::string& equation)
{
    std::vector<std::string> tokens;
    std::string current_token;
    int len = equation.length();
    bool func_flag = false;
    for (int i = 0; i!=len ; i++)
    {
        char s {equation[i]};
        if (isdigit(s) || s == '.')
        {
            current_token += s;
            continue;
        } 
        else if (isoperator(s))
        {
            if (current_token != "") {tokens.push_back(current_token);}
            tokens.push_back(std::string{s});
            current_token = "";
        }
        else if (isalpha(s))
        {
            current_token += s;
            func_flag = true;
            continue;
        }
        else if (s == '(')
        {
            current_token += equation[i];
            if (!func_flag)
            {
                std::cout << "encountered ( without function.\n";
                tokens.push_back(current_token);
                current_token = "";
            }
            else
            {
                std::cout << "outer (\n";
                int counter = 1;
                for (int j = i+1; j!=len;j++)
                {
                    current_token += equation[j];

                    if (equation[j] == '(')
                    {
                        counter ++;
                        std::cout << "inner (\n";
                    }
                    if (equation[j] == ')')
                    {
                        counter --;
                        if (!counter)
                        {
                            i = j;
                            std::cout << "outer )\n";
                            func_flag = 0;
                            break;
                        }
                        std::cout << "inner )\n";
                    }
                }
            }
        }
        else if (s == ')' && (!func_flag))
        {

                std::cout << "encountered ) without function.\n";
                tokens.push_back(current_token);
                tokens.push_back(std::string{s});
                current_token = "";
                
        }

        
    }
    if (current_token != "") {tokens.push_back(current_token);}
    return tokens;
}

bool isoperator(char s)
{
    char a[] {'+', '-', '/', '*', '^'};
    for (char i : a)
    {
        if (i == s)
        {
            return true;
        }
    }
    return false;
}