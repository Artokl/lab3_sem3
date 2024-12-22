#ifndef DICTIONARYAPP_H
#define DICTIONARYAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include "../IDictionary.h"

class DictionaryApp final : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout;
    QPushButton *loadFileButton;
    QPushButton *analyzeButton;
    QTextEdit *outputArea;
    QLineEdit *filePathLineEdit;
    QLabel *statusLabel;

    IDictionary<QString, int> dictionary;

public:
    explicit DictionaryApp(QWidget *parent = nullptr);

    private slots:
        void loadFile();
    void analyzeText();
};

#endif // DICTIONARYAPP_H
