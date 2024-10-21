#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include "shunting_yard/shunting_yard.hpp"
#include "expression_solver/expression_solver.hpp"

bool is_second_of_greater_precedence(std::string& first, std::string& second, std::map<std::string, int>& order);
double cot (double X){return 1/std::tan(X);}
// bool isoperator(char s);
bool isoperator(std::string s);
bool isNumber(std::string expr);
bool isBinOperator(std::string s);
void tokenize(std::vector<std::string>& tokens, int index);
bool isUnsolved(std::string expr);
bool isSingOperator(std::string s);

double plus(double a, double b){return a+b;}
double minus(double a, double b){return a-b;}
double mul(double a, double b){return a*b;}
double div(double a, double b){return a/b;}
double power(double a, double b){return std::pow(a,b);}




struct FuncDef 
{
    FUNC p;
    std::string name;
} MONO_FUNCTIONS[8]
{
    FuncDef{std::cos,     "cos"},
    FuncDef{std::sin,     "sin"},
    FuncDef{std::tan,     "tan"},
    FuncDef{     cot,     "cot"},
    FuncDef{std::exp,     "exp"},
    FuncDef{std::log,     "ln" },
    FuncDef{std::log2,   "log2"},
    FuncDef{std::log10, "log10"}
};


int main(int argc, char** argv)
{
    std::map<std::string, int> order;

    order["+"] = 0;
    order["-"] = 0;
    order["*"] = 1;
    order["/"] = 1;
    order["^"] = 2;
    order["("] = -1;
    order[")"] = -1;
    order["cos"] = 3;
    order["tan"] = 3;
    order["cot"] = 3;
    order["sin"] = 3;
    order["ln"] = 3;
    order["log2"] = 3;
    order["log10"] = 3;
    
    


    const double pi = 3.14159265358979323846;
    const double e = std::exp(1.0);
    std::vector<std::string> tokens { "-sin(-1)"};
    std::pair<std::string, std::string> consts[4]
    {
    {"-e", std::to_string(-e)},
    {"e",std::to_string(e)},
    {"-pi", std::to_string(-pi)},
    {"pi", std::to_string(pi)}
    };
    int token_index = 0;
    for (auto element : consts)
    {
        int search = tokens[token_index].find(element.first);
        if (search != -1)
        {
            
            tokens[token_index].erase(tokens[token_index].begin()+search , tokens[token_index].begin()+search + element.first.length());
            tokens[token_index].insert(tokens[token_index].begin()+search, element.second.begin(), element.second.end());
        }
    }
    while (token_index != tokens.size())
    {

        
        if (isUnsolved(tokens[token_index]))
        {
            tokenize(tokens, token_index);
            token_index--;
        }
        token_index ++;
    
    }


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

        if (isNumber(i))
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
            while ((!oper.empty()) && is_second_of_greater_precedence(i,oper.top(),order))
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
        if (isBinOperator(i))
        {
            
            std::string b = oper.top();
            oper.pop();
            std::string a = oper.top();
            oper.pop();
            std::cout << "a: " << a << " b: " << b <<   " oper: \"" << i << "\"\n";
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
        else if (isSingOperator(i))
        {
            std::string b = oper.top();
            oper.pop();
            double (*oper_f)(double);
            for (auto j : MONO_FUNCTIONS)
            {
                if (j.name == i)
                {
                    oper_f = j.p;
                }
            }
            oper.push(std::to_string(oper_f(std::stod(b))));
            continue;
        }
        oper.push(i);
    }
    std::cout<<oper.top();

    
    return 0;
}

void tokenize(std::vector<std::string>& tokens, int index)
{
    std::string current_token;
    std::string equation = tokens[index];
    tokens.erase(tokens.begin()+index, tokens.begin()+index+1);
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
        else if (isoperator(std::string{s}))
        {
            if (current_token != "") 
            {
                tokens.insert(tokens.begin()+index, current_token);
                index++;

                }
            tokens.insert(tokens.begin()+index, std::string{s});
            index++;
            
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
            
            if (!func_flag)
            {
                std::cout << "encountered ( without function.\n";
                current_token += equation[i];
                if (current_token != "") 
                
                {
                    tokens.insert(tokens.begin()+index, current_token);
                    index++;
                }
                current_token = "";
            }
            else
            {
                std::cout << "outer (\n";
                int counter = 1;
                if (current_token != "") 
                {
                    tokens.insert(tokens.begin()+index, current_token);
                    index++;
                    }
                tokens.insert(tokens.begin()+index, "(");
                index++;
                current_token = "";
                for (int j = i+1; j!=len;j++)
                {
                    
                    

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
                            if (current_token != "") 
                            {
                                tokens.insert(tokens.begin()+index, current_token);
                                index++;
                                
                            }

                           tokens.insert(tokens.begin()+index, ")");
                            index++;
                            current_token="";
                            std::cout << "outer )\n";
                            func_flag = 0;
                            break;
                        }
                        std::cout << "inner )\n";
                    }
                    current_token += equation[j];
                }
            }
        }
        else if (s == ')' && (!func_flag))
        {

                std::cout << "encountered ) without function.\n";
                if (current_token != "") 
                {
                    tokens.insert(tokens.begin()+index, current_token);
                    index++;
                }
                
                tokens.insert(tokens.begin()+index, ")");
                index++;
                current_token = "";
                
        }

        
    }
    if (current_token != "") 
    {
        tokens.insert(tokens.begin()+index, current_token);
        index++;
    }
}

// bool isoperator(char s)
// {
//     char a[] {'+', '-', '/', '*', '^'};
//     for (char i : a)
//     {
//         if (i == s)
//         {
//             return true;
//         }
//     }
//     return false;
// }

bool isoperator(std::string s)
{
    std::string op { "+-/*^"};
    if (op.find(s)!=-1 || isSingOperator(s)){return true;}
    return false;
}

bool isBinOperator(std::string s)
{
    std::string op { "+-/*^"};
    if (op.find(s)==-1 || s.length()>1){return false;}
    return true;
}
bool isSingOperator(std::string s)
{
    for (FuncDef i : MONO_FUNCTIONS)
    {
        if (i.name == s)
        {
            return true;
        }
    }
    
    return false;
}



bool is_second_of_greater_precedence(std::string& first, std::string& second, std::map<std::string, int>& order)
{
    std::cout << "I tried ";
    std::cout << "comparing \"" << first << "\" and \"" << second << "\" and it's ";
    


    // std::cout  << order[first]  << " ? " << order[second] << "\n"; 
    bool res = order[first] <= order[second];  
    std::cout << res << "\n";
    return res;

}

bool isUnsolved(std::string expr)
{
    bool contains_operators = 0, contains_digits = 0, contains_brackets = 0;
    bool unarPlusFlag = 1, unarMinusFlag = 1;
    for (char a : expr)
    {
        if ((a == '(' )|| (a==')')){contains_brackets =1;}
        if (isdigit(a) || a =='.')
        {
            contains_digits=1;
        }
        else if (isalpha(a) || isBinOperator(std::string{a}))
        {
            if (a == '-' && unarMinusFlag)
            {
                unarMinusFlag =0;
                continue;
            }
            if (a == '+' && unarMinusFlag)
            {
                unarPlusFlag =0;
                continue;
            }
            contains_operators=1;
        }
        if (contains_digits && contains_operators)
        {
            return 1;
        }

        if (contains_brackets && contains_operators)
        {
            return 1;
        }
        
    }
    return 0;
    
}

bool isNumber(std::string expr)
{
    bool contains_digits = 0;
    bool unarPlusFlag = 1, unarMinusFlag = 1;
    for (char a : expr)
    {
        if (isdigit(a) || a =='.')
        {
            contains_digits=1;
        }
        if (a == '(' || a==')'){return false;}
        if (isoperator(std::string{a}))
        {
            if (a == '-' && unarMinusFlag)
            {
                unarMinusFlag =0;
                continue;
            }
            if (a == '+' && unarMinusFlag)
            {
                unarPlusFlag =0;
                continue;
            }
            return false;
        }
        
    }
    if (contains_digits){return true;}
    return false;
    
}



