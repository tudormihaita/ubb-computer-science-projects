#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulare_Practice1.h"

class Simulare_Practice1 : public QMainWindow
{
    Q_OBJECT

public:
    Simulare_Practice1(QWidget *parent = nullptr);
    ~Simulare_Practice1();

private:
    Ui::Simulare_Practice1Class ui;
};
