#ifndef SORTEDSEQUENCEAPP_H
#define SORTEDSEQUENCEAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include "../ISortedSequence.h"

class SortedSequenceApp : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout;
    QPushButton *addButton;
    QLineEdit *inputField;
    QTextEdit *outputArea;
    ISortedSequence<int> sortedSequence;

public:
    explicit SortedSequenceApp(QWidget *parent = nullptr);

    private slots:
        void addElement();
    void updateOutput();
};

#endif // SORTEDSEQUENCEAPP_H
