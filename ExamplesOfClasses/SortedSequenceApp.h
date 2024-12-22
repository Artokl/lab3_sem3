#ifndef SORTEDSEQUENCEAPP_H
#define SORTEDSEQUENCEAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include "../ISortedSequence.h"

class SortedSequenceApp : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout;
    QLineEdit *inputField;
    QPushButton *addButton;
    QComboBox *orderSelector; // Комбобокс для выбора порядка сортировки
    QTextEdit *outputArea;
    ISortedSequence<int> sortedSequence;

public:
    explicit SortedSequenceApp(QWidget *parent = nullptr);

    private slots:
        void addElement();
    void updateOutput();
    void orderChanged(int index); // Слот для обработки изменений выбора в QComboBox
};

#endif // SORTEDSEQUENCEAPP_H
