#pragma once

class Building
{
private:
    static int latestID;
    int maxAge, initialCost, currentAge, ID;

public:
    Building(int maxAge, int initialCost);
    int GetCost();
    void ToAge(int years);
    bool IsDestroyed();

private:
    void Destroy();
};
