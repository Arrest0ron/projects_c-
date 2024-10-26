#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <iomanip>
#include "shunting_yard/shunting_yard.hpp"
#include "expression_solver/expression_solver.hpp"
#include <sstream>
#include <string>

bool is_second_of_greater_precedence(std::string& first, std::string& second, std::map<std::string, int>& order);
double cot (double X){return 1/std::tan(X);}
// bool isoperator(char s);
bool isoperator(std::string s);
bool isNumber(std::string expr);
bool isBinOperator(std::string s);
bool isBinOperator(char s);
void tokenize(std::vector<std::string>& tokens, int index);
bool isUnsolved(std::string expr);
bool isSingOperator(std::string s);
std::string strip(std::string& expr);

double plus(double a, double b){return a+b;}
double minus(double a, double b){return a-b;}
double mul(double a, double b){return a*b;}
double div(double a, double b){return a/b;}
double power(double a, double b){return std::pow(a,b);}



std::string to_string_with_precision(double value, int precision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}


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

    
    // std::cout << isUnsolved("1-36");

    // return 0;
    
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


    // std::string a = to_string_with_precision(-123.1231231212, 10);
    std::cout.precision(15);
    std::cout << std::fixed << std::setprecision(10);
    // return 0;
    std::vector<std::string> tokens {" e^(-2.5)"};


    // tokenize(tokens, 0);



    // return 0;
    for (std::string& i : tokens)
    {
        i = strip(i);
        // std::cout << i << "\n";
    }
    // for (auto i : tokens)
    // {
    //    std::cout << i;
    // }
    // return 0;
    std::pair<std::string, std::string> consts[4]
    {
    {"-e", to_string_with_precision(-e,10)},
    {"e",to_string_with_precision(e,10)},
    {"-pi", to_string_with_precision(-pi,10)},
    {"pi", to_string_with_precision(pi,10)}
    };
    int token_index = 0;
    for (int i = 0; i!= 4; i++)
    {
        auto element = consts[i];
        int search = tokens[token_index].find(element.first);
        if (search != -1)
        {
            i--;
            tokens[token_index].erase(tokens[token_index].begin()+search , tokens[token_index].begin()+search + element.first.length());
            tokens[token_index].insert(tokens[token_index].begin()+search, element.second.begin(), element.second.end());
        }
    }
    while (token_index != tokens.size())
    {
        // std::cout << token_index << " index.\n";
        if (isUnsolved(tokens[token_index]))
        {
            tokenize(tokens, token_index);
            token_index--;
            std::cout << "Unsolved token found.\n";
        }
        token_index ++;
    }
    for (std::string& i : tokens)
    {
        std::cout << i << "\"\n";
    }

    // return 0;

    std::queue<std::string> output;
    std::stack<std::string> oper;

    // std::cout << is_second_of_greater_precedence(g,l);
    // for (auto i : tokens)
    // {
    //     std::cout << i << ";\n";
    // }
    // output.push(0);
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
        if (oper.top() == "(" || oper.top() == "(")
        {
            std::cout << "warning: " << oper.top() << " in output stack (could be due () in start)\n";
            oper.pop();
            continue;
        }
        output.push(oper.top());
        oper.pop();
    }


    while(!output.empty())
    {
        std::string i = output.front();
        std::string temp = "";
        output.pop();
        if (isBinOperator(i))
        {
            std::string b = oper.top();
            std::string a;
            oper.pop();
            if ((i == "+" || i == "-") && oper.empty())
            {
                a = "0";
            }
            else
            {
                a = oper.top();
                oper.pop();
            }
            
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
                // std::cout << i << "\n";
                oper_f = power;
            }    
            
            
            temp = to_string_with_precision(oper_f(std::stod(a), std::stod(b)),10);
            if (temp == "nan" || temp == "-nan")
            {
                oper.push("0.0");
                std::cout << "Warning: NaN result\n";
                continue;
            }
            if (temp == "inf" || temp == "-inf")
            {
                throw(std::runtime_error("INF RESULT"));
            }
            oper.push(temp);
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
            temp = to_string_with_precision(oper_f(std::stod(b)),10);
            if (temp == "nan" || temp == "-nan")
            {
                oper.push(0);
                std::cout << "Warning: NaN result\n";
            }
            if (temp == "inf" || temp == "-inf")
            {
                throw(std::runtime_error("INF RESULT"));
            }
            oper.push(temp);
            
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

bool isBinOperator(char s)
{
    std::string op { "+-/*^"};
    if (op.find(s)==-1){return false;}
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
    int operators_amount = 0, operands_amount = 0;
    int standart_part = 0;   // 0 = nothing yet, 1 = only operator, 2 = both 
    if (expr.size() == 1){return 0;}

    for (char c : expr)
    {
        if (c == '-' || c == '+'){operands_amount++;}
        // if (isalpha(c)){return 1;}
        if (c == '(' || c == ')'){operands_amount++;}
        if (operands_amount>1){return 1;}
        if (c == '*' || c == '/' || c == '^'){return 1;}
    }
    for (char c : expr)
    {
        if ((c == '-' || c == '+' ) && (standart_part == 0)){standart_part = 1;}
        if (( isdigit(c) || c == '.' ) && ((standart_part == 1) || (standart_part == 0) )){standart_part = 2;}
        if ((c == '-' || c == '+' ) && (standart_part == 2)){return 1;}
    }

    return 0;
    
}

bool isNumber(std::string expr)
{
    bool contains_digits = 0;
    bool unarPlusFlag = 1, unarMinusFlag = 1;
    for (char a : expr)
    {
        if (isalpha(a)){return 0;}
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

std::string strip(std::string& expr)
{

    std::string newstr;
    for (char i : expr)
    {
        if (i!=' ')
        {
            newstr +=i;
        }
    }
    return newstr;
}

