#include "SortedSequenceApp.h"

SortedSequenceApp::SortedSequenceApp(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    setWindowTitle("ISortedSequence");
    resize(1200, 800);

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите число для добавления в последовательность...");

    addButton = new QPushButton("Добавить элемент", this);
    connect(addButton, &QPushButton::clicked, this, &SortedSequenceApp::addElement);

    // Создание комбобокса для выбора порядка сортировки
    orderSelector = new QComboBox(this);
    orderSelector->addItem("По возрастанию");
    orderSelector->addItem("По убыванию");
    connect(orderSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SortedSequenceApp::orderChanged);

    outputArea = new QTextEdit(this);
    outputArea->setReadOnly(true);

    layout->addWidget(inputField);
    layout->addWidget(addButton);
    layout->addWidget(orderSelector);
    layout->addWidget(outputArea);
}

void SortedSequenceApp::addElement() {
    bool ok;
    const int value = inputField->text().toInt(&ok);
    if (ok) {
        sortedSequence.Add(value);
        updateOutput();
        inputField->clear();
    } else {
        outputArea->append("Ошибка: введите корректное число.");
    }
}

void SortedSequenceApp::updateOutput() const {
    auto sequence = sortedSequence.GetSequence();

    // Определяем порядок сортировки на основе выбранного элемента в QComboBox
    if (orderSelector->currentText() == "По возрастанию") {
        std::ranges::sort(sequence);
    } else {
        std::ranges::sort(sequence, std::greater<>());
    }

    outputArea->clear();
    outputArea->append("Текущая последовательность:");
    for (const auto &value : sequence) {
        outputArea->append(QString::number(value));
    }
}

void SortedSequenceApp::orderChanged([[maybe_unused]] int index) const {
    // Обновляем отображение при изменении порядка
    updateOutput();
}
