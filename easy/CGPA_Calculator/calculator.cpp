#include <iostream>
#include <limits>
#include "calculator.hpp"

int main(int argc, char** argv)
{ 
    unsigned classes_amount = input_classes_amount();
    int* all_marks = new int[classes_amount];
    input_marks(all_marks, classes_amount); 
    CGPA_calculation_output(all_marks, classes_amount);
    delete[] all_marks;
    return 0;
}

int input_classes_amount()
{
    unsigned classes_amount{};
    std::cout << "Amount of classes taken: ";
    while (classes_amount<1)
    {
        std::cin >> classes_amount;
        if (std::cin && classes_amount < 1)
        {
            std::cout << "You should have at least one class before calculating your CGPA.\n";
            continue;
        }
        if (!std::cin)
        {
            std::cout << "Sorry, invalid classes amount. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return classes_amount;
}

void input_marks(int* all_marks, int classes_amount)
{
    int counter = 0;
    while (counter++ != classes_amount)
    {   
        std::cout << "Enter your score: ";
        int class_mark;
        std::cin >> class_mark;
        if (!std::cin)
        {
            std::cout << "Sorry, invalid classes amount. Try again: ";
            counter--;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        all_marks[counter-1] = class_mark;
    }
}

float CGPA_calculation_output(const int* all_marks, int classes_amount)
{
    std::cout << "_____________________\n\n";
    float totalscore;
    for (int i =0; i!= classes_amount; i++)
    {
        std::cout << "class №" << i << ": " << all_marks[i] << "\n";
        totalscore += all_marks[i];
    }
    
    std::cout << "_____________________\nTotal: " << totalscore << "\n";


    float CGPA = totalscore / static_cast<float>(classes_amount);
    std::cout << "Your CGPA evaluates to: " << CGPA << "\n";
    return CGPA;
}



