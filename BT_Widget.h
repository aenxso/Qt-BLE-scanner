#ifndef BT_WIDGET_H
#define BT_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class BT_Widget; }
QT_END_NAMESPACE

class BT_Widget : public QWidget
{
    Q_OBJECT

public:
    BT_Widget(QWidget *parent = nullptr);
    ~BT_Widget();

private:
    Ui::BT_Widget *ui;
};
#endif // BT_WIDGET_H
