#include <iostream>
#include <cstdlib>
#include <ctime>

class Dice
{
public:
    Dice(unsigned int seed)
    {
        std::srand(seed);
    }

    void play();

private:
    int roll()
    {
        return (std::rand() % 6) + 1;
    }
};
void Dice::play()
{
    int point = 0;
    while (true)
    {
        int roll1 = roll();
        int roll2 = roll();
        int sum = roll1 + roll2;
        std::cout << "掷骰子: " << roll1 << " + " << roll2 << " = " << sum << std::endl;

        if (point == 0)
        {
            if (sum == 7 || sum == 11)
            {
                std::cout << "你赢了!" << std::endl;
                break;
            }
            else if (sum == 2 || sum == 3 || sum == 12)
            {
                std::cout << "你输了!" << std::endl;
                break;
            }
            else
            {
                point = sum;
                std::cout << "你的点数是 " << point << std::endl;
            }
        }
        else
        {
            if (sum == point)
            {
                std::cout << "你赢了!" << std::endl;
                break;
            }
            else if (sum == 7)
            {
                std::cout << "你输了!" << std::endl;
                break;
            }
        }
    }
}
int main()
{
    unsigned int seed;
    std::cout << "请输入种子: ";
    std::cin >> seed;

    Dice game(seed);
    game.play();

    return 0;
}
