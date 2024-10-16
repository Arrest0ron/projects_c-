#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

int user_input();

int main()
{
    char* RPS[] = {"Rock", "Paper", "Scissors"};
    std::cout << "Let's play a game... Choose: 1 for Rock, 2 for Paper and 3 for Scissors?...\n";
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(0,2);
    int computer = dist(mt);
    
    int user = user_input();
    char* computer_IS = RPS[computer];
    char* user_IS = RPS[user];
    std::cout << "You quickly showed the " << user_IS << " and \ncomputer responded with the " << computer_IS << "!\n";
    if (computer==user)
    {
        std::cout << "It's a tie!\n";
    }
    else if ((computer+1)%3 == user)
    {
        std::cout << "You won!\n";
    }
    else 
    {
        std::cout << "You lost :< \n";
    }    
    return 0;
}

int user_input()
{
    int input = 0;
    while ((0 >= input) || (input >= 4))
    {
        std::cin >> input;
    }
    
    return input-1;
}
