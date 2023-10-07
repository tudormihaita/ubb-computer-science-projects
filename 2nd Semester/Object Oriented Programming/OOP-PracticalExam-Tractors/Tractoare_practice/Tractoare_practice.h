#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tractoare_practice.h"

class Tractoare_practice : public QMainWindow
{
    Q_OBJECT

public:
    Tractoare_practice(QWidget *parent = nullptr);
    ~Tractoare_practice();

private:
    Ui::Tractoare_practiceClass ui;
};
