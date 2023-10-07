#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TicTacToe_practice.h"

class TicTacToe_practice : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToe_practice(QWidget *parent = nullptr);
    ~TicTacToe_practice();

private:
    Ui::TicTacToe_practiceClass ui;
};
