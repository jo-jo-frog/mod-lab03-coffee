#include "Automata.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

class CoffeeMenu {
public:
    static const unordered_map<string, double>& GetMenu() {
        static unordered_map<string, double> menu = {
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

class Automata {
public:
    enum class Status {
        OFF,
        WAIT,
        CHECK,
        ACCEPT,
        COOK
    };

    Automata() : cash(0.0), state(Status::OFF) {}

    void On() {
        state = Status::WAIT;
    }

    void Off() {
        state = Status::OFF;
    }

    void Coin(double deposit) {
        state = Status::ACCEPT;
        cash += deposit;
    }

    void etMenu(int choice) {
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
        if (choice == 0){
          ifstream file("menu.txt");
          string line;
            if (file.is_open()){
              while (getline(file, line)){
                stringstream ss(line);
                string orderName;
                double orderPrice;
                getline(ss, orderName, ',');
                ss >> orderPrice;
                menu.push_back(orderName);
                prices.push_bacl(orderPrice);
              }
              file.close();
            }
          else{
            cout << "Ошибка открытия файла" << endl;
          } 
        }

        for (int i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i] << " цена: " << prices[i] << endl;
        }
    }

    void getState() {
        cout << "Текущее состояние: ";
        switch (state) {
            case Status::OFF:   cout << "OFF"; break;
            case Status::WAIT:  cout << "WAIT"; break;
            case Status::CHECK: cout << "CHECK"; break;
            case Status::ACCEPT:cout << "ACCEPT"; break;
            case Status::COOK:  cout << "COOK"; break;
        }
        cout << endl;
    }

    void Choice(int choice) {
        if (state != Status::ACCEPT) {
            cout << "Вы не внесли денег" << endl;
            return;
        }
        if (menu.empty()) {
            cout << "Меню еще не загружено" << endl;
            return;
        }
        if (choice < 0 || choice >= static_cast<int>(menu.size())) {
            cout << "Неверный номер напитка" << endl;
            return;
        }
        if (Check(choice)) {
            cout << "Выбрано " << menu[choice] << endl;
            Cook(choice);
        } else {
            cout << "Необходимо внести еще: " << (prices[choice] - cash) << endl;
            state = Status::CHECK;
        }
    }

    bool Check(int choice) {
        if (cash < prices[choice]) {
            cout << "Ошибка: недостаточно средств" << endl;
            return false;
        } else {
            cash -= prices[choice];
            cout << "Остаток на балансе: " << cash << endl;
            return true;
        }
    }

    void Cancel() {
        if (cash > 0) {
            cout << "Возврат " << cash << " рублей" << endl;
        }
        cash = 0.0;
        state = Status::WAIT;
    }

    void Cook(int choice) {
        state = Status::COOK;
        cout << "Готовится " << menu[choice] << "..." << endl;
        Finish(choice);
    }

    void Finish(int choice) {
        cout << menu[choice] << " готов" << endl;
        state = Status::WAIT;
    }

private:
    double cash;
    vector<string> menu;
    vector<double> prices;
    Status state;
};
