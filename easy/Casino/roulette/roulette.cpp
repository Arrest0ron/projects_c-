#include <random>
#include <iostream> 
#include "roulette.hpp"

Roulette::Roulette(long seed)

    {
        this->gamble = new char*[3] {"Zero", "Black", "Red"};
        std::mt19937* a = new std::mt19937{seed};
        MT = a;
    }
    
void Roulette::Spin(int* cash)
{
    if (*cash <= 0)
    {
        std::cout << "Insufficient balance...\n";
        return;
    }
    int amount, bet;
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
    std::cout << "Please, enter your bet 0, Black, Red (0,1,2): ";
    while (true)
    {
        std::cin >> bet;

        if ((bet > 2) || (bet <0))
        {
            std::cout << "You have to bet on 0, Black (1), or Red (2). Enter the number from 0 to 2: ";
            continue;
        }
        std::cout << "You put " << amount << " on " << gamble[bet]<< "\n";
        break;
    }

    std::uniform_int_distribution<int> dist {0, 36};
    int result = dist(*MT);
    std::cout << "The ball lands on " << result << ", ";
    
    if (result%2 == 1){std::cout << gamble[1] << "\n";}
    else if ((result%2 == 0 ) && (result!=0)){std::cout << gamble[2] << "\n";}
    else {if (result%2 == 1){std::cout  << gamble[0] << "\n";}}
    bool eq = (result == bet) || (result%2 == bet%2 && (bet!=0));
    if (eq and (result!=0))
    {
        std::cout << "You've won " << amount*2 << "$, congratulations!\n";
        *cash+=amount*2;
    }
    else if (eq and (result == 0))
    {
        std::cout << "You've won BIG, +" << amount*35 << "$, congratulations!\n";
        *cash+=amount*35;
    }
    else
    {
        std::cout << "You lost " << amount << "$\n";
        *cash-=amount;
    }

    std::cout << "You have " << *cash << "$.\n";


}

Roulette::~Roulette()
    {
        delete[] gamble;
    }
