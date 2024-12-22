#include "DictionaryApp.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

DictionaryApp::DictionaryApp(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    // Устанавливаем заголовок окна
    setWindowTitle("IDictionary");

    // Устанавливаем размеры окна (например, увеличиваем в два раза от стандартных значений)
    resize(1200, 800); // 1200x800 пикселей (по сравнению с размером по умолчанию)

    filePathLineEdit = new QLineEdit(this);
    filePathLineEdit->setPlaceholderText("Выберите файл для анализа...");
    filePathLineEdit->setReadOnly(true);

    loadFileButton = new QPushButton("Загрузить файл", this);
    connect(loadFileButton, &QPushButton::clicked, this, &DictionaryApp::loadFile);

    analyzeButton = new QPushButton("Анализировать текст", this);
    analyzeButton->setEnabled(false);
    connect(analyzeButton, &QPushButton::clicked, this, &DictionaryApp::analyzeText);

    outputArea = new QTextEdit(this);
    outputArea->setReadOnly(true);

    statusLabel = new QLabel("Ожидание загрузки файла...", this);

    layout->addWidget(filePathLineEdit);
    layout->addWidget(loadFileButton);
    layout->addWidget(analyzeButton);
    layout->addWidget(outputArea);
    layout->addWidget(statusLabel);
}

void DictionaryApp::loadFile() {
    if (const QString filePath = QFileDialog::getOpenFileName(this, "Выберите текстовый файл", "", "Текстовые файлы (*.txt)"); !filePath.isEmpty()) {
        filePathLineEdit->setText(filePath);
        statusLabel->setText("Файл загружен. Нажмите \"Анализировать текст\".");
        analyzeButton->setEnabled(true);
    }
}

void DictionaryApp::analyzeText() {
    const QString filePath = filePathLineEdit->text();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    dictionary = IDictionary<QString, int>();

    while (!in.atEnd()) {
        QString line = in.readLine();
        for (QStringList words = line.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts); const QString &word : words) {
            QString lowerWord = word.toLower();
            try {
                const int count = dictionary.Get(lowerWord);
                dictionary.Remove(lowerWord);
                dictionary.Add(lowerWord, count + 1);
            } catch (std::out_of_range &) {
                dictionary.Add(lowerWord, 1);
            }
        }
    }

    file.close();

    // Собираем все ключи и значения из словаря
    QVector<std::pair<QString, int>> sortedWords;
    for (int i = 0; i < dictionary.Size(); ++i) {
        try {
            QString key = dictionary.GetKeyAtIndex(i); // Новый метод для получения ключа
            int value = dictionary.Get(key);
            sortedWords.append({key, value});
        } catch (std::out_of_range &) {
            continue;
        }
    }

    // Сортируем слова по убыванию частоты
    std::ranges::sort(sortedWords, [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    // Выводим результат
    outputArea->clear();
    for (const auto &pair : sortedWords) {
        outputArea->append(QString("%1: %2").arg(pair.first).arg(pair.second));
    }

    statusLabel->setText("Анализ завершен!");
}
