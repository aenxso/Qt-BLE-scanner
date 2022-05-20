#include "BT_Widget.h"
#include "ui_bt_widget.h"

BT_Widget::BT_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BT_Widget)
{
    ui->setupUi(this);
}

BT_Widget::~BT_Widget()
{
    delete ui;
}

