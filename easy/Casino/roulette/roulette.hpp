#ifndef roulette_HPP
#define roulette_HPP
#include <random>

class Roulette
{
    char** gamble;
    std::mt19937* MT;
    

    public:

    Roulette(std::random_device* seed);
    void Spin(int* cash);
    ~Roulette();
};
#endif //roulette_HPP