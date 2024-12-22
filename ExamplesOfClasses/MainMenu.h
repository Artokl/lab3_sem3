#ifndef MAINMENUAPP_H
#define MAINMENUAPP_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "DictionaryApp.h"
#include "SortedSequenceApp.h"

class MainMenuApp : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout;
    QPushButton *dictionaryButton;
    QPushButton *sequenceButton;

public:
    explicit MainMenuApp(QWidget *parent = nullptr);

    private slots:
        void openDictionaryApp();
    void openSortedSequenceApp();
};

#endif // MAINMENUAPP_H
