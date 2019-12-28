#include "widget.h"
#include "ui_widget.h"
#include "Backtrack.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getN()
{
    QString a = ui->lineEdit_n->text();
    return a.toInt();
}

void Widget::getSolution()
{
    NQueens queen;
    int algorithm = ui->comboBox->currentIndex();
    nqueens = queen.solveNQueens(getN(), algorithm);
    time = queen.getTime();
}

int Widget::getBoardWidth()
{
    int w = width();
    int h = height();
    return w < h ? w : h;
}

int Widget::getGridWidth()
{
    int width = getBoardWidth();
    QString a = ui->lineEdit_n->text();
    int n = a.toInt();
    return (width - 2 * boardMargin) / n;
}

void Widget::adjustPosition()
{
    QString a = ui->lineEdit_n->text();
    int n = a.toInt();
    //窗口大小
    this->resize(height() + 100 + 120, height());

    int xspace = (width() - (boardMargin + n * getGridWidth())) / 4;
    //int yspace = height() - 100;
    //复选框
    ui->comboBox->resize(2 * xspace, 40);
    ui->comboBox->move(width() - 3 * xspace, 50);
    //标签
    ui->label->move(width() - 3 * xspace, 50 + 60);
    ui->label_width->move(width() - 3 * xspace + 60, 50 + 60);
    ui->label_2->move(width() - 3 * xspace, 50 + 90);
    ui->label_height->move(width() - 3 * xspace + 60, 50 + 90);
    ui->label_3->move(width() - 3 * xspace, 50 + 120);
    ui->label_time->move(width() - 3 * xspace + 60, 50 + 120);
    //单行输入框
    ui->lineEdit_n->resize(2 * xspace, 40);
    ui->lineEdit_n->move(width() - 3 * xspace, height() - 50 - 100);
    //RUN按钮
    ui->pushButton_run->resize(2 * xspace, 40);
    ui->pushButton_run->move(width() - 3 * xspace, height() - 50 - 40);
}

void Widget::paintEvent(QPaintEvent *event)
{
    int n = getN();//皇后数
    //打印窗口大小
    ui->label_width->setText(QString::number(width()));
    ui->label_height->setText(QString::number(height()));

    //动态调整部件位置
    adjustPosition();

    QPainter painter(this);
//    QPen pen=painter.pen();
//    pen.setColor(QColor("#8D5822"));
//    pen.setWidth(7);
//    painter.setPen(pen);
//    pen.setColor(Qt::black);
//    pen.setWidth(1);
//    painter.setPen(pen);
    //QPen pen; // 调整线条宽度
    //pen.setWidth(2);
    //painter.setPen(pen);
//    painter.drawLine(50,50,150,150);
//    painter.drawLine(50,50,100,200);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    // 绘制棋盘
    for (int i = 0; i < n+1; i++)
    {
        painter.drawLine(boardMargin + getGridWidth() * i, boardMargin, boardMargin + getGridWidth() * i, boardMargin + n * getGridWidth());
        painter.drawLine(boardMargin, boardMargin + getGridWidth() * i, boardMargin + n * getGridWidth(), boardMargin + getGridWidth() * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if(!nqueens.empty())
    {
        vector<string> res=nqueens.front();
        //绘制第一种解法
        QImage image;
        image.load("D:/mxy/Documents/QtProject/NQueens/NQueens/img/queen.png");
        QImage scaledImage = image.scaled(getGridWidth(), getGridWidth(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        for(int i=0;i < res.size();i++)
        {
            string e=res[i];
            for(int j=0;j < e.size();j++)
            {
                char c=e[j];
                if(c=='Q')
                {
//                    QRectF target(10.0, 20.0, 80.0, 60.0);
//                    QRectF source(10.0, 20.0, 80.0, 60.0);
                    painter.drawImage(boardMargin + j * getGridWidth(), boardMargin + i * getGridWidth(), scaledImage);
                    //painter.drawText(boardMargin + getGridWidth() / 2 + j * getGridWidth(), boardMargin + getGridWidth() / 2 + i * getGridWidth(),"queen");
                }
            }
        }
    }
}

//下拉选框有选项被选中时
void Widget::on_comboBox_activated(const QString &arg1)
{

}

//点击RUN按钮运行程序
void Widget::on_pushButton_run_clicked()
{
    NQueens queen;
    getSolution();

    //打印耗时
    QString time_string = QString::number(time, 'f', 4);//以浮点数格式输出，小数点后保留四位
    time_string.append('s');
    ui->label_time->setText(time_string);

    update();
//    repaint();
}
