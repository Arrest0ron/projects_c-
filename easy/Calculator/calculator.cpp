#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include "shunting_yard/shunting_yard.hpp"
#include "expression_solver/expression_solver.hpp"

bool is_second_of_greater_precedence(std::string& first, std::string& second);
double cot (double X){return 1/std::tan(X);}
bool isoperator(char s);
bool isoperator(std::string s);
std::vector<std::string> tokenize(std::string& equation);

double plus(double a, double b){return a+b;}
double minus(double a, double b){return a-b;}
double mul(double a, double b){return a*b;}
double div(double a, double b){return a/b;}
double power(double a, double b){return std::pow(a,b);}

FuncDef _cos{std::cos, "cos("};



int main(int argc, char** argv)
{
    
    const double pi = 3.14159265358979323846;
    const double e = std::exp(1.0);
    std::string a = "5.5 * (2.3 + 4.8^2) / (3.7 - 1.2) + 8.1 - (6.2 / (1.5^3)) + 3.9^2 * 7.1 / (2.0 + 1.5)";
    // std::cout << isoperator ("^") << "!\n";

    std::vector<std::string> tokens = tokenize(a);
    std::queue<std::string> output;
    std::stack<std::string> oper;

    // std::cout << is_second_of_greater_precedence(g,l);
    for (auto i : tokens)
    {
        std::cout << i << ";\n";
    }
    int c = 0;
    for (auto i : tokens)

    {
        c++;

        if (isdigit(i[0]))
        {
            output.push(i);
        }
        else if (isoperator(i))
        {
            
            if (oper.empty())
            {
                oper.push(i);
                continue;
            }
            // std::cout << oper.top() << "current oper top.\n";
            while ((!oper.empty()) && is_second_of_greater_precedence(i,oper.top()))
            {
                output.push(oper.top());
                oper.pop();
            }
            oper.push(i);
            
        }
        if (i == "(")
        {
            oper.push(i);
        }
        if (i == ")")
        {
            while (oper.top() != "(")
            {
                output.push(oper.top());
                oper.pop();
            }
            oper.pop();
        }
    }

    while (!oper.empty())
    {
        output.push(oper.top());
        oper.pop();
    }

    while(!output.empty())
    {
        std::string i = output.front();
        
        output.pop();
        if (isoperator(i))
        {
            
            std::string b = oper.top();
            oper.pop();
            std::string a = oper.top();
            oper.pop();
            std::cout << "a: " << a << " b: " << b << std::endl;
            double (*oper_f)(double,double);
            if (i=="+") 
            {
                oper_f = plus;
            }
            if (i=="-") 
            {
                oper_f = minus;
            }
            if (i=="*") 
            {
                oper_f = mul;
            }
            if (i=="/") 
            {
                oper_f = div;
            }
            if (i=="^") 
            {
                std::cout << i << "\n";
                oper_f = power;
            }    
            oper.push(std::to_string(oper_f(std::stod(a), std::stod(b))));
            continue;
        }
        oper.push(i);
    }
    std::cout<<oper.top();

    
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
                if (current_token != "") {tokens.push_back(current_token);}
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
                if (current_token != "") {tokens.push_back(current_token);}
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

bool isoperator(std::string s)
{
    std::string op { "+-/*^"};
    if (op.find(s)==-1){return false;}
    return true;
}

bool is_second_of_greater_precedence(std::string& first, std::string& second)
{
    std::cout << "I tried ";
    std::cout << "comparing \"" << first << "\" and \"" << second << "\" and it's ";
    
    std::map<std::string, int> order;
    order["+"] = 0;
    order["-"] = 0;
    order["*"] = 1;
    order["/"] = 1;
    order["^"] = 2;
    order["("] = -1;
    order[")"] = -1;
    // std::cout  << order[first]  << " ? " << order[second] << "\n"; 
    bool res = order[first] <= order[second];
    std::cout << res << "\n";
    if (res){return true;}
    return false;

}