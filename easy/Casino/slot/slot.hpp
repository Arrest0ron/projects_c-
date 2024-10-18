#ifndef slot_HPP
#define slot_HPP
#include <random>

class Slot
{
    char** gamble;
    std::mt19937* MT;
    

    public:

    Slot(long seed);
    void Spin(int* cash);
    ~Slot();
};
#endif //slot_HPP