#include <random>
#include <iostream> 
#include "slot.hpp"

Slot::Slot(std::random_device* seed)

    {
        this->gamble = new char*[4] {"Seven", "Bar", "Banana", "Cherry"};
        std::mt19937* a = new std::mt19937{(*seed)()};
        MT = a;
    }
    
void Slot::Spin(int* cash)
{
    if (*cash <= 0)
    {
        std::cout << "Insufficient balance...\n";
        return;
    }
    int amount;
    std::cout << "Please, enter the amount: ";
    
    while (true)
    {
        std::cin >> amount;

        if (amount > *cash)
        {
            std::cout << "\nThis amount exeeds your balance of " <<  *cash << ". Try again: ";
            continue;
        }
        break;
    }
    int results[3] = {0,0,0};
    std::uniform_int_distribution<int> dist {0, 3};

    for (int i = 0; i!= 3; i++)
    {
        results[i] = dist(*MT);
    }
    
    std::cout << std::endl << gamble[results[0]] << "  " << gamble[results[1]] << "  " << gamble[results[2]] << "\n";
    
    bool eq = (results[0] == results [1]) && (results[1] == results[2]);
    if (eq and (results[0]!=0))
    {
        std::cout << "You've won " << amount*10 << "$, congratulations!\n";
        *cash+=amount*10;
    }
    else if (eq and (results[0] == 0))
    {
        std::cout << "You've won BIG, +" << amount*28 << "$, congratulations!\n";
        *cash+=amount*28;
    }
    else
    {
        std::cout << "You lost " << amount << "$\n";
        *cash-=amount;
    }

    std::cout << "You have " << *cash << "$.\n";


}

Slot::~Slot()
    {
        delete[] gamble;
    }
