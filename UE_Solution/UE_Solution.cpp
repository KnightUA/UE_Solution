#include <iostream>

#include "Building.h"

int RequestMaxAgeFromConsole()
{
    int maxAge = -1;
    while (maxAge <= 0)
    {
        std::cout << "Please enter max building age: ";
        std::cin >> maxAge;
        if (maxAge <= 0)
        {
            std::cout << "Max age should be more then 0";
        }
    }

    return maxAge;
}

int RequestInitialCostFromConsole()
{
    int initialCost = -1;
    while (initialCost < 0)
    {
        std::cout << "Please enter initial cost of building: ";
        std::cin >> initialCost;
        if (initialCost < 0)
        {
            std::cout << "Initial cost shouldn't be negative";
        }
    }

    return initialCost;
}

bool IsValidAction(int action)
{
    switch (action)
    {
    case 1:
    case 2:
        return true;
    default:
        return false;
    }
}

int RequestActionsFromConsole()
{
    int action = -1;
    while (!IsValidAction(action))
    {
        std::cout << "*** Available actions ***\n";
        std::cout << "1. To add age to the building\n";
        std::cout << "2. Show cost of building\n";
        std::cout << "Enter action number: ";
        std::cin >> action;

        if (!IsValidAction(action))
        {
            std::cout << "Incorrect action number. Please check available actions\n";
        }
    }

    return action;
}


int RequestYearsFromConsole()
{
    int years = -1;
    while (years < 0)
    {
        std::cout << "Please enter years to apply for building: ";
        std::cin >> years;
        if (years < 0)
        {
            std::cout << "Years shouldn't be negative";
        }
    }

    return years;
}

bool IsValidAnswer(const char& answer)
{
    return answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N';
}

bool RequestAnswerForPlayAgainFromConsole()
{
    char answer;
    while (!IsValidAnswer(answer))
    {
        std::cout << "Do you want to play again? (Y/N) ";
        std::cin >> answer;
        if (!IsValidAnswer(answer))
        {
            std::cout << "Incorrect symbol";
        }
    }

    if (answer == 'y' || answer == 'Y')
    {
        return true;
    }

    if (answer == 'n' || answer == 'N')
    {
        return false;
    }

    return false;
}

int main(int argc, char* argv[])
{
    bool bIsPlaying = true;

    while (bIsPlaying)
    {
        Building* building = new Building(RequestMaxAgeFromConsole(), RequestInitialCostFromConsole());

        while (!building->IsDestroyed())
        {
            switch (RequestActionsFromConsole())
            {
            case 1:
                building->ToAge(RequestYearsFromConsole());
                break;
            case 2:
                std::cout << "Building cost " << building->GetCost() << "\n";
                break;
            default:
                std::cout << "Unhandled action!\n";
            }
        }

        bIsPlaying = RequestAnswerForPlayAgainFromConsole();

        delete building;
    }
    return 0;
}
