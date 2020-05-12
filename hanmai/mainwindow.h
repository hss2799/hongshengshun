#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>


struct User
{
	QString str;
	int len;
    int xi_;
    QString name;
    int mai_;
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void qudiaoStr(QString &qudiao, QStringList& List);
    void addTableItem(QString str, int r,int c,bool red=false);
    void addTableItemJieGuo(QString str, int r,int c,bool red=false);
private slots:
    void on_pb_zhengli_clicked();

    void on_pb_tongji_clicked();

    void on_pb_jiequ_clicked();

private:
    Ui::MainWindow *ui;
    QStringList zhengliList;
    QList<User> m_zhengliUser;
    QList<User> m_tongjiUser;
};

#endif // MAINWINDOW_H
