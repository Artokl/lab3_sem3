#include "MainMenu.h"


MainMenuApp::MainMenuApp(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    setWindowTitle("Main Menu");
    resize(400, 200);

    dictionaryButton = new QPushButton("Словарь", this);
    connect(dictionaryButton, &QPushButton::clicked, this, &MainMenuApp::openDictionaryApp);

    sequenceButton = new QPushButton("Сортированная последовательность", this);
    connect(sequenceButton, &QPushButton::clicked, this, &MainMenuApp::openSortedSequenceApp);

    layout->addWidget(dictionaryButton);
    layout->addWidget(sequenceButton);
}

void MainMenuApp::openDictionaryApp() {
    auto *dictionaryWindow = new DictionaryApp();
    dictionaryWindow->setAttribute(Qt::WA_DeleteOnClose);
    dictionaryWindow->show();
}

void MainMenuApp::openSortedSequenceApp() {
    auto *sequenceWindow = new SortedSequenceApp();
    sequenceWindow->setAttribute(Qt::WA_DeleteOnClose);
    sequenceWindow->show();
}
