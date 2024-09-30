#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Інтерфейс Observer (слухач)
class Observer {
public:
    virtual void Update(int health) = 0; // Метод, який буде викликаний при оновленні
    virtual ~Observer() = default;
};

// Інтерфейс Observable (спостережуваний об'єкт)
class Observable {
public:
    virtual void AddObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    virtual void RemoveObserver(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void Notify(int health) {
        for (auto& observer : observers) {
            observer->Update(health);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};

// Клас Hero (спостережуваний об'єкт)
class Hero : public Observable {
public:
    Hero(std::string name, int health) : name(std::move(name)), health(health) {}

    void TakeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << " takes " << damage << " damage! Health is now " << health << ".\n";
        Notify(health);
    }

    void RestoreHealth(int amount) {
        health += amount;
        std::cout << name << " restores " << amount << " health! Health is now " << health << ".\n";
        Notify(health);
    }

    std::string GetName() const {
        return name;
    }

    int GetHealth() const {
        return health;
    }

private:
    std::string name;
    int health;
};

// Клас HealthBar (слухач)
class HealthBar : public Observer {
public:
    HealthBar(std::shared_ptr<Hero> hero) : hero(std::move(hero)) {
        this->hero->AddObserver(std::shared_ptr<Observer>(this)); // Підписуємось на зміни здоров'я героя
    }

    void Update(int health) override {
        std::cout << "HealthBar: Hero " << hero->GetName() << " has " << health << " health left.\n";
    }

private:
    std::shared_ptr<Hero> hero;
};

int main() {
    std::shared_ptr<Hero> hero = std::make_shared<Hero>("John", 100);
    std::shared_ptr<HealthBar> healthBar = std::make_shared<HealthBar>(hero);

    hero->TakeDamage(30);  // Герой отримує 30 урону
    hero->RestoreHealth(20); // Герой відновлює 20 здоров'я
    hero->TakeDamage(50);  // Герой отримує 50 урону

    return 0;
}