#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    Ui::Widget *ui;
    int boardMargin = 50;//棋盘边缘

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int getBoardWidth();//获取棋盘宽度
    int getGridWidth();//获取格子宽度

private:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_comboBox_activated(const QString &arg1);
    void on_pushButton_run_clicked();
};
#endif // WIDGET_H
