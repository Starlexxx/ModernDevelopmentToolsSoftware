#include <iostream>
#include <string>
#include <map>
#include <memory>

struct Instrument
{
    std::string  name;
    std::string  brand;
    std::string  model;
    int     cost;
    bool    isAvailable;
};

int main()
{
    std::multimap<int, std::shared_ptr<Instrument>> musicShop
    {
        {1, std::make_shared<Instrument>(Instrument {"Guitar", "Ibanez", "RGA-FX100", 700, true})},
        {2, std::make_shared<Instrument>(Instrument {"Guitar", "Gibson", "flying-V", 800, false})},
        {3, std::make_shared<Instrument>(Instrument {"Ukulele", "Flight", "NUC310", 70, true})},
    };

    for(auto o : musicShop)
        std::cout << o.second->name << ' ' <<  o.second->brand  << ' '
                  << o.second->model  << ' ' << o.second->cost << ' '
                  << o.second->isAvailable << ' ' << std::endl;
    return 0;
}
