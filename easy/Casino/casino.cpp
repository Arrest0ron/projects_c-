#include "slot/slot.hpp"
#include "roulette/roulette.hpp"
#include <iostream>
#include <limits>

int choice()
{
    std::cout << "What do you want?\n0.Play roulette.\n1.Spin the slot.\n2.Leave the casino\n" ;
    int input;
    while (true)
    {
        
        
        std::cin >> input;
        if ((input > 2) || (input <0))
        {
            std::cout << "Please, enter the number from 0 to 2: ";
            continue;
        } 
        else if (!std::cin)
        {
            std::cout << "Wrong input. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        break;
    }
    return input;
}
int main(int argc, char** argv)

{
    srand(time(0));
    int balance = 50000+rand()%50000;
    Roulette Roul(balance);
    Slot Sl (balance);
    bool loop = true;
    while (loop)
    {
        switch (choice())
        {
        case 0:
            Roul.Spin(&balance);
            break;
        case 1:
            
            Sl.Spin(&balance);
            break;
        case 2: 
            loop = false;
            break;
        default:    
            break;
        }
    }

    return 0;
}