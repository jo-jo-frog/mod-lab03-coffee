// Copyright 2026 Anisimov Kirill
#include <iostream>
#include "Automata.h"

int main() {
    std::cout << "=== Демонстрация работы кофейного автомата ===" << std::endl;
    std::cout << std::endl;

    Automata machine;
    std::cout << "1. Автомат создан" << std::endl;
    machine.getState();
    std::cout << std::endl;

    std::cout << "2. Включение автомата" << std::endl;
    machine.On();
    machine.getState();
    std::cout << std::endl;

    std::cout << "3. Загрузка меню" << std::endl;
    machine.etMenu(1);
    std::cout << std::endl;

    std::cout << "4. Внесение 200 рублей" << std::endl;
    machine.Coin(200);
    machine.getState();
    std::cout << std::endl;

    std::cout << "5. Выбор напитка: Капучино (индекс 2)" << std::endl;
    machine.Choice(2);
    machine.getState();
    std::cout << std::endl;

    std::cout << "6. Попытка купить Латте (индекс 3)" << std::endl;
    machine.Choice(3);
    machine.getState();
    std::cout << std::endl;

    std::cout << "7. Добавление 200 рублей" << std::endl;
    machine.Coin(200);
    machine.getState();
    std::cout << std::endl;

    std::cout << "8. Повторный выбор Латте (индекс 3)" << std::endl;
    machine.Choice(3);
    machine.getState();
    std::cout << std::endl;

    std::cout << "9. Отмена сеанса" << std::endl;
    machine.Cancel();
    machine.getState();
    std::cout << std::endl;

    std::cout << "10. Выключение автомата" << std::endl;
    machine.Off();
    machine.getState();
    std::cout << std::endl;

    std::cout << "=== Демонстрация завершена ===" << std::endl;

    return 0;
}
