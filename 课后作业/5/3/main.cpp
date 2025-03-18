#include <iostream>
class fuel;
class engine
{
    friend class fuel;

private:
    int powerlevel;

public:
    engine() { powerlevel = 0; }
    void engine_fn(fuel &f);
};
class fuel
{
    friend class engine;

private:
    int fuellevel;

public:
    fuel() { fuellevel = 0; }
    void fuel_fn(engine &e);
};

void engine::engine_fn(fuel &f)
{
    f.fuellevel += 10;
    std::cout << "Fuel level增加到: " << f.fuellevel << std::endl;
}

void fuel::fuel_fn(engine &e)
{
    e.powerlevel += 20;
    std::cout << "Engine power level增加到: " << e.powerlevel << std::endl;
}

signed main()
{
    engine e;
    fuel f;

    e.engine_fn(f);
    f.fuel_fn(e);
    return 0;
}