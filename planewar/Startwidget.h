#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Startwidget; }
QT_END_NAMESPACE

class Startwidget : public QWidget
{
    Q_OBJECT

public:
    Startwidget(QWidget *parent = nullptr);
    ~Startwidget();

    void setButtonStyle(QPushButton * button, const QString & filename);

signals:
    void startGame();  // 开始游戏信号
    void exitGame();   // 退出游戏信号

private slots:
    void on_startButton_clicked();  // 开始按钮点击事件
    void on_exitButton_clicked();   // 退出按钮点击事件
    void setbackground(const QString & filename);
private:
    Ui::Startwidget *ui;

};

#endif // STARTWIDGET_H
