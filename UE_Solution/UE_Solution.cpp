#include <iostream>

const int MAX_HERO_HEALTH = 1000;
const int MIN_HERO_HEALTH = 100;

const int MAX_ITEM_DISTANCE = 100;
const int MIN_ITEM_DISTANCE = 0;

int main(int argc, char* argv[])
{
    float item_impact, item_distance, result_impact;
    float max_health;

    std::cout << "=====================================================\n";
    std::cout << "Before start game, please enter Hero's health between " << MIN_HERO_HEALTH << " and " <<
        MAX_HERO_HEALTH << ": ";
    std::cin >> max_health;

    while (max_health > MAX_HERO_HEALTH || max_health < MIN_HERO_HEALTH)
    {
        std::cout << "Incorrect value. Hero's health should be between " << MIN_HERO_HEALTH << " and " <<
            MAX_HERO_HEALTH << ": ";
        std::cin >> max_health;
    }

    float health = max_health;
    std::cout << "=====================================================\n";
    std::cout << "You have a Hero with health equal " << health << '\n';
    std::cout << "=====================================================\n";
    
    while (health > 0)
    {
        std::cout << "Please enter an item usage distance between " << MIN_ITEM_DISTANCE << " and " << MAX_ITEM_DISTANCE
            << ": ";
        std::cin >> item_distance;

        if (item_distance > MAX_ITEM_DISTANCE)
        {
            std::cout << "The distance is more then " << MAX_ITEM_DISTANCE <<
                ". Hero won't take any effect from item.\n";
        }
        else if (item_distance < MIN_ITEM_DISTANCE)
        {
            std::cout << "Distance can't be negative. Hero won't take any effect from item.\n";
        }
        else
        {
            std::cout << "Please enter an item impact: ";
            std::cin >> item_impact;

            result_impact = item_impact * (1 - item_distance / MAX_ITEM_DISTANCE);

            if (result_impact > 0)
            {
                std::cout << "Hero has been healed by " << result_impact << '\n';
            }
            else if (result_impact < 0)
            {
                std::cout << "Hero has been damaged by " << result_impact << '\n';
            }
            else
            {
                std::cout << "In the result item haven't any impact. Hero won't take any effect from item.\n";
            }

            health = std::ceil(health + result_impact);
            if (health > MAX_HERO_HEALTH)
            {
                health = MAX_HERO_HEALTH;
                std::cout << "Hero can't have health more then " << MAX_HERO_HEALTH << '\n';
            }
            else if (health < 0)
            {
                health = 0;
            }
        }

        std::cout << "=====================================================\n";
        std::cout << "Hero's health is " << health << '\n';
        std::cout << "=====================================================\n";
    }

    std::cout << "It was nice game, but your Hero is dead\n";

    return 0;
}
