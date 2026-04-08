#include <iostream>
#include "Automata.h"

using namespace std;

int main() {
    cout << "=== Демонстрация работы кофейного автомата ===" << endl;
    cout << endl;
    
    Automata machine;
    cout << "1. Автомат создан" << endl;
    machine.getState();
    cout << endl;

    cout << "2. Включение автомата" << endl;
    machine.On();
    machine.getState();
    cout << endl;
    
    cout << "3. Загрузка меню" << endl;
    machine.etMenu(1);
    cout << endl;
    
    cout << "4. Внесение 200 рублей" << endl;
    machine.Coin(200);
    machine.getState();
    cout << endl;
    
    cout << "5. Выбор напитка: Капучино (индекс 2)" << endl;
    machine.Choice(2);
    machine.getState();
    cout << endl;
    
    cout << "6. Попытка купить Латте (индекс 3)" << endl;
    machine.Choice(3);
    machine.getState();
    cout << endl;
    
    cout << "7. Добавление 200 рублей" << endl;
    machine.Coin(200);
    machine.getState();
    cout << endl;
    
    cout << "8. Повторный выбор Латте (индекс 3)" << endl;
    machine.Choice(3);
    machine.getState();
    cout << endl;
    
    cout << "9. Отмена сеанса" << endl;
    machine.Cancel();
    machine.getState();
    cout << endl;
    
    cout << "10. Выключение автомата" << endl;
    machine.Off();
    machine.getState();
    cout << endl;
    
    cout << "=== Демонстрация завершена ===" << endl;
    
    return 0;
}
