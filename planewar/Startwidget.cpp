#include "Startwidget.h"
#include "ui_Startwidget.h"
#include "config.h"
#include <QPixmap>
#include <QFile>
#include <QIcon>
#include <QPalette>


Startwidget::Startwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Startwidget)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    setWindowTitle("飞机大战 v1.0");
    setWindowIcon(QIcon(GAME_ICON));
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setbackground(START_BACKGROUND);
    setButtonStyle(ui->startButton,":/beijing/icon_9qxh2l2sxns/kaishiyouxi.png");
    setButtonStyle(ui->exitButton,":/beijing/icon_9qxh2l2sxns/tuichuyouxi.png");
}

Startwidget::~Startwidget()
{
    delete ui;
}

//设置图标
void Startwidget::setButtonStyle(QPushButton * button, const QString & filename)
{   button->setFixedSize(50,50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(ui->startButton->width(),ui->startButton->height()));
    button->setStyleSheet("background-color:transparent");
}

// 开始按钮点击事件
void Startwidget::on_startButton_clicked()
{
    emit startGame();  // 发出开始游戏信号
}

// 退出按钮点击事件
void Startwidget::on_exitButton_clicked()
{
    emit exitGame();  // 发出退出游戏信号
}

//设置背景
void Startwidget::setbackground(const QString &filename)
{
    QPixmap pixmap(filename);
    //获取当前窗口大小
    QSize windowSize = this->size();

    //将图片照片缩放到当前窗口大小
    QPixmap scalePixmap = pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //创建QPattle对象并设置照片背景图片--调色板
    QPalette palette = this-> palette();
    palette.setBrush(QPalette::Window,QBrush(scalePixmap));

    //将调色板应用到窗口上
    this->setPalette(palette);
}


