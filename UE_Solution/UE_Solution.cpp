#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class Weapon
{
public:
    virtual float GetDamage() = 0;
    virtual std::string GetName() = 0;
    virtual ~Weapon() = default;
};

class Shield : public Weapon
{
public:
    float GetDamage() override
    {
        return 10.f;
    }

    std::string GetName() override
    {
        return "Shield";
    }
};

class Sword : public Weapon
{
public:
    float GetDamage() override
    {
        return 25.f;
    }

    std::string GetName() override
    {
        return "Sword";
    }
};

class Hammer : public Weapon
{
public:
    float GetDamage() override
    {
        return 50.f;
    }

    std::string GetName() override
    {
        return "Hammer";
    }
};

class Character
{
public:
    Character(std::string name) : name(std::move(name)), currentWeapon(nullptr)
    {
    }

    bool AddWeaponToSlot(std::unique_ptr<Weapon>& weapon)
    {
        if (weapon.get() == nullptr)
        {
            std::cout << "You can't add unavailable weapon.\n";
            return false;
        }

        if (weapons.size() >= MAX_WEAPONS)
        {
            std::cout << "You have reached the maximum number of weapons.\n";
            return false;
        }

        weapons.push_back(std::move(weapon));
        return true;
    }

    void RemoveSelectedWeapon()
    {
        if (currentWeapon == nullptr) return;

        for (auto it = weapons.begin(); it != weapons.end(); ++it)
        {
            if (it->get() == currentWeapon)
            {
                weapons.erase(it);
                currentWeapon = nullptr;
                break;
            }
        }
    }

    void SetWeapon(std::unique_ptr<Weapon>& weapon)
    {
        if (weapon.get() == nullptr)
        {
            std::cout << "You can't set unavailable weapon.\n";
            return;
        }

        for (const auto& w : weapons)
        {
            if (w.get() == weapon.get())
            {
                currentWeapon = weapon.get();
                return;
            }
        }

        std::cout << "Weapon not found in the slots.\n";
    }

    void ChooseWeaponFromSlot(int slot)
    {
        if (slot < 0 || slot >= weapons.size())
        {
            std::cout << "Invalid weapon slot.\n";
            return;
        }
        SetWeapon(weapons[slot]);
    }

    void SwitchToNextWeapon()
    {
        if (!currentWeapon) return;

        for (size_t i = 0; i < weapons.size(); ++i)
        {
            if (weapons[i].get() == currentWeapon && i + 1 < weapons.size())
            {
                SetWeapon(weapons[i + 1]);
                return;
            }
        }
    }

    void SwitchToPreviousWeapon()
    {
        if (!currentWeapon) return;

        for (size_t i = 0; i < weapons.size(); ++i)
        {
            if (weapons[i].get() == currentWeapon && i > 0)
            {
                SetWeapon(weapons[i - 1]);
                return;
            }
        }
    }

    Weapon* GetCurrentWeapon() const
    {
        return currentWeapon;
    }

    std::string GetCurrentWeaponName() const
    {
        return currentWeapon ? currentWeapon->GetName() : "No Weapon";
    }

    std::vector<std::unique_ptr<Weapon>>& GetAllAvailableWeapons()
    {
        return weapons;
    }

    std::string GetName() const
    {
        return name;
    }

private:
    std::string name;
    std::vector<std::unique_ptr<Weapon>> weapons;
    Weapon* currentWeapon;
    static const size_t MAX_WEAPONS = 5;
};

int main()
{
    std::unique_ptr<Character> character = std::make_unique<Character>("John");

    std::unique_ptr<Weapon> hammer = std::make_unique<Hammer>();
    std::unique_ptr<Weapon> shield = std::make_unique<Shield>();
    std::unique_ptr<Weapon> sword = std::make_unique<Sword>();

    character->AddWeaponToSlot(hammer);
    character->AddWeaponToSlot(shield);
    character->AddWeaponToSlot(sword);

    std::cout << character->GetName() << " has " << character->GetCurrentWeaponName() << " in hands.\n";

    character->ChooseWeaponFromSlot(0);
    std::cout << character->GetName() << " has " << character->GetCurrentWeaponName() << " in hands.\n";

    character->ChooseWeaponFromSlot(1);
    std::cout << character->GetName() << " has " << character->GetCurrentWeaponName() << " in hands.\n";

    character->ChooseWeaponFromSlot(2);
    std::cout << character->GetName() << " has " << character->GetCurrentWeaponName() << " in hands.\n";

    return 0;
}