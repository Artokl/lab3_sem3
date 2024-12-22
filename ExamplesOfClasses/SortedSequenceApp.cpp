#include "SortedSequenceApp.h"

SortedSequenceApp::SortedSequenceApp(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    setWindowTitle("Sorted Sequence App");
    resize(1200, 800);

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите число для добавления в последовательность...");

    addButton = new QPushButton("Добавить элемент", this);
    connect(addButton, &QPushButton::clicked, this, &SortedSequenceApp::addElement);

    outputArea = new QTextEdit(this);
    outputArea->setReadOnly(true);

    layout->addWidget(inputField);
    layout->addWidget(addButton);
    layout->addWidget(outputArea);
}

void SortedSequenceApp::addElement() {
    bool ok;
    int value = inputField->text().toInt(&ok);
    if (ok) {
        sortedSequence.Add(value);
        updateOutput();
        inputField->clear();
    } else {
        outputArea->append("Ошибка: введите корректное число.");
    }
}

void SortedSequenceApp::updateOutput() {
    const auto sequence = sortedSequence.GetSequence();
    outputArea->clear();
    outputArea->append("Текущая последовательность:");
    for (const auto &value : sequence) {
        outputArea->append(QString::number(value));
    }
}
