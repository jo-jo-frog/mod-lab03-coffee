// Copyright 2026 Anisimov Kirill
#include "Automata.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

class CoffeeMenu {
 public:
  static const std::map<std::string, double>& GetMenu() {
    static std::map<std::string, double> menu = {
        {"Эспрессо", 120.50},
        {"Американо", 150.00},
        {"Капучино", 180.00},
        {"Латте", 190.00},
        {"Моккачино", 210.00},
        {"Раф", 230.00},
        {"Глясе", 200.00}
    };
    return menu;
  }
};

Automata::Automata() : cash(0.0), state(Status::OFF) {}

void Automata::On() {
  state = Status::WAIT;
}

void Automata::Off() {
  state = Status::OFF;
}

void Automata::Coin(double deposit) {
  state = Status::ACCEPT;
  cash += deposit;
}

void Automata::etMenu(int choice) {
  if (choice == 1) {
    const auto& staticMenu = CoffeeMenu::GetMenu();
    int len = staticMenu.size();
    menu.resize(len);
    prices.resize(len);
    int i = 0;
    for (const auto& item : staticMenu) {
      menu[i] = item.first;
      prices[i] = item.second;
      ++i;
    }
  }
  if (choice == 0) {
    std::ifstream file("menu.txt");
    std::string line;
    if (file.is_open()) {
      menu.clear();
      prices.clear();
      while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string orderName;
        double orderPrice;
        std::getline(ss, orderName, ',');
        ss >> orderPrice;
        menu.push_back(orderName);
        prices.push_back(orderPrice);
      }
      file.close();
    } else {
      std::cout << "Ошибка открытия файла" << std::endl;
    }
  }

  for (size_t i = 0; i < menu.size(); ++i) {
    std::cout << i + 1 << ". " << menu[i]
          << " цена: " << prices[i] << std::endl;
  }
}

void Automata::getState() {
  std::cout << "Текущее состояние: ";
  switch (state) {
    case Status::OFF:   std::cout << "OFF"; break;
    case Status::WAIT:  std::cout << "WAIT"; break;
    case Status::CHECK: std::cout << "CHECK"; break;
    case Status::ACCEPT: std::cout << "ACCEPT"; break;
    case Status::COOK:  std::cout << "COOK"; break;
  }
  std::cout << std::endl;
}

void Automata::Choice(int choice) {
  if (state != Status::ACCEPT) {
    std::cout << "Вы не внесли денег" << std::endl;
    return;
  }
  if (menu.empty()) {
    std::cout << "Меню еще не загружено" << std::endl;
    return;
  }
  if (choice < 0 || choice >= static_cast<int>(menu.size())) {
    std::cout << "Неверный номер напитка" << std::endl;
    return;
  }
  if (Check(choice)) {
    std::cout << "Выбрано " << menu[choice] << std::endl;
    Cook(choice);
  } else {
    std::cout << "Необходимо внести еще: "
              << (prices[choice] - cash) << std::endl;
    state = Status::CHECK;
  }
}

bool Automata::Check(int choice) {
  if (cash < prices[choice]) {
    std::cout << "Ошибка: недостаточно средств" << std::endl;
    return false;
  } else {
    cash -= prices[choice];
    std::cout << "Остаток на балансе: " << cash << std::endl;
    return true;
  }
}

void Automata::Cancel() {
  if (cash > 0) {
    std::cout << "Возврат " << cash << " рублей" << std::endl;
  }
  cash = 0.0;
  state = Status::WAIT;
}

void Automata::Cook(int choice) {
  state = Status::COOK;
  std::cout << "Готовится " << menu[choice] << "..." << std::endl;
  Finish(choice);
}

void Automata::Finish(int choice) {
  std::cout << menu[choice] << " готов" << std::endl;
  state = Status::WAIT;
}
