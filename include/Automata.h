// Copyright 2026 Anisimov Kirill
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Automata {
public:
    enum class Status {
        OFF,
        WAIT,
        CHECK,
        ACCEPT,
        COOK
    };

    Automata();

    void On();
    void Off();
    void Coin(double deposit);
    void etMenu(int choice);
    void getState();
    void Choice(int choice);
    bool Check(int choice);
    void Cancel();
    void Cook(int choice);
    void Finish(int choice);

    // Геттеры для тестов
    double getCash() const { return cash; }
    Status getStatus() const { return state; }
    bool isMenuLoaded() const { return !menu.empty(); }
    int getMenuSize() const { return menu.size(); }
    std::string getMenuName(int index) const { return menu[index]; }
    double getPrice(int index) const { return prices[index]; }

private:
    double cash;
    std::vector<std::string> menu;
    std::vector<double> prices;
    Status state;
};

#endif  // AUTOMATA_H
