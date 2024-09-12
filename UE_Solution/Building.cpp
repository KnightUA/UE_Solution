#include "Building.h"

#include <iostream>
#include <ostream>

int Building::latestID = 0;

Building::Building(int maxAge, int initialCost)
{
    this->maxAge = maxAge;
    this->initialCost = initialCost;
    this->currentAge = 0;
    this->ID = latestID;

    latestID += 1;
}

int Building::GetCost()
{
    if (currentAge >= maxAge)
    {
        return 0;
    }

    if (currentAge == 0)
    {
        return initialCost;
    }

    float ageRatio = static_cast<float>(currentAge) / maxAge;
    int cost = initialCost - static_cast<int>(initialCost * ageRatio);

    return cost;
}

void Building::ToAge(int years)
{
    currentAge += years;
    if (currentAge > maxAge)
    {
        Destroy();
    }
}

void Building::Destroy()
{
    std::cout << "Building with ID(" << ID << ") is destroyed. Current age of building is " << currentAge <<
        " of his maxAge " << maxAge <<
        std::endl;
}

bool Building::IsDestroyed()
{
    return currentAge >= maxAge;
}
