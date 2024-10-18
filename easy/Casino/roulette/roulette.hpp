#ifndef roulette_HPP
#define roulette_HPP
#include <random>

class Roulette
{
    char** gamble;
    std::mt19937* MT;
    

    public:

    Roulette(long seed);
    void Spin(int* cash);
    ~Roulette();
};
#endif //roulette_HPP