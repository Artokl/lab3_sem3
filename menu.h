#ifndef TRAINING_SFML_MENU_H
#define TRAINING_SFML_MENU_H

#include <iostream>
#include <QApplication>

#include "StyleSheetUtils.h"
#include "TicTacToe/GameWindow.h"
#include "Tests/Summary_Tests.h"
#include "ExamplesOfClasses//MainMenu.h"

using namespace std;

inline void print_choose_prog() {
    std::cout << "_____________________________________________________________\n";
    std::cout << "Select the actions:\n" <<
         "0) Exit\n" <<
         "1) TicTacToe\n" <<
         "2) Tests\n" <<
         "3) Examples of how classes work\n" <<
         "Enter: ";
}


inline void print_menu(int argc, char *argv[]) {
    print_choose_prog();
    int var_prog;
    std::cin >> var_prog;

    if (var_prog == 0) {
        // Выход из программы
        return;
    } else if (var_prog == 1) {
        // Запуск игры крестики-нолики
        GameWindow game;
        game.run();
        print_menu(argc, argv);
    } else if (var_prog == 2) {
        // Запуск тестов
        tests();
        print_menu(argc, argv);
    } else if (var_prog == 3) {
        // Пример работы со словарем или последовательностью
        std::cout << "_____________________________________________________________\n";
        std::cout << "Launching Main Menu...\n";
        QApplication app(argc, argv);
        applyStyleSheet(app);
        MainMenuApp mainMenu;
        mainMenu.show();
        app.exec(); // Запуск GUI-приложения
        print_menu(argc, argv);
    } else {
        // Обработка неверного выбора
        std::cout << "Wrong choice\n";
        print_menu(argc, argv);
    }
}


#endif // TRAINING_SFML_MENU_H
