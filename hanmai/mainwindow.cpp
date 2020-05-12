#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

#pragma execution_character_set("utf-8")



bool ListSortUser(const User info1, const User info2)
{
    bool bSort = true;

    if(info1.xi_  < info2.xi_)
    {
        bSort = true;
    }
    else if(info1.xi_  == info2.xi_)
    {
        if(info1.mai_ > info2.mai_)
            bSort = true;
        else
            bSort = false;
    }
    else
    {
        bSort = false;
    }
    return bSort;
}

bool ListSort2(const QString info1, const QString info2)
{
    return info1.length()  > info2.length();  //降序排列
}

bool ListSort(const QString info1, const QString info2)
{

    bool bSort = true;

    if(info1.length()  > info2.length())
    {
        bSort = true;
    }
    else if(info1.length()  == info2.length())
    {
        if(info1.left(1).toInt()  < info2.left(1).toInt())
            bSort = true;
        else
            bSort = false;
    }
    else
    {
        bSort = false;
    }
    return bSort;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::qudiaoStr(QString &qudiao, QStringList& List)
{
    qudiao = qudiao.simplified();
    foreach (QString str, List)
    {
        qudiao.replace(str,"");
    }
    qudiao = qudiao.simplified();
}



void MainWindow::addTableItem(QString str, int r,int c,bool red)
{
    if(c >= ui->tableWidget->columnCount())
        return;

    if(r >= ui->tableWidget->columnCount())
        ui->tableWidget->setRowCount(r+1);

    QTableWidgetItem*item =  ui->tableWidget->item(r,c);
    if(item == 0)
    {
        item = new QTableWidgetItem(str);
        ui->tableWidget->setItem(r,c,item);
    }
    item->setText(str);
    item->setTextAlignment(Qt::AlignCenter);
    if(red)
    {
        item->setBackground(Qt::red);
    }
    else
        item->setBackground(Qt::white);
}

void MainWindow::addTableItemJieGuo(QString str, int r,int c,bool red)
{
    if(c >= ui->tableWidget_jieguo->columnCount())
        return;

    if(r >= ui->tableWidget_jieguo->columnCount())
        ui->tableWidget_jieguo->setRowCount(r+1);

    QTableWidgetItem*item =  ui->tableWidget_jieguo->item(r,c);
    if(item == 0)
    {
        item = new QTableWidgetItem(str);
        ui->tableWidget_jieguo->setItem(r,c,item);
    }
    item->setText(str);
    item->setTextAlignment(Qt::AlignCenter);
    if(red)
    {
        item->setBackground(Qt::red);
    }
    else
        item->setBackground(Qt::white);
}
//整理
void MainWindow::on_pb_zhengli_clicked()
{
    QString qudiao =  ui->textEdit_qudiao->toPlainText();
    QStringList qudiaoList = qudiao.split("\n");


    QString jielong =  ui->textEdit_jielong->toPlainText();
    QStringList jielongList = jielong.split("\n");

    zhengliList.swap(QStringList());

    foreach (QString str, jielongList)
    {
        qudiaoStr(str,qudiaoList);
        if(!str.isEmpty())
        {
            zhengliList << str;
        }
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(zhengliList.size());

    qSort(zhengliList.begin(), zhengliList.end(), ListSort);

    m_zhengliUser.swap(QList<User>());
    for(int i= 0 ; i < zhengliList.size();i++)
    {
        QString str = zhengliList.at(i);
        addTableItem(str,i,0);

        int num = 6;
        addTableItem(QString::number(num),i,1);

        QString strTmp;
        if(str.length() < num)
        {
            strTmp = str;
        }
        else
        {
            strTmp = str.left(num);
        }

        QString strTmp1 = strTmp.left(1);
        if(strTmp1.toInt() > 0)
        {
            User user;
			user.str = str;
			user.len = num;
            user.xi_ = strTmp1.toInt();
            addTableItem(QStringLiteral("%1系").arg(strTmp1),i,2);

            int len = strTmp.length();
            int n=0;

            if(len > 2)
            {
               QString  c1 = strTmp.mid(len-1,1);
               QString  c2 = strTmp.at(len-2);
                n = c2.toInt()*10;
                n += c1.toInt();

            }
            if(n > 10)
                user.name = (strTmp.mid(1,len-3));
            else if(n > 0)
                user.name = (strTmp.mid(1,len-2));
            else
                user.name = (strTmp.mid(1,len-1));

            addTableItem(user.name,i,3);
            if(n == 0)
                n = 1;
            user.mai_ = n;
            addTableItem(QString::number(n),i,4);
            m_zhengliUser.push_back(user);
        }
        else
        {
            addTableItem(QStringLiteral("未知"),i,2,true);
        }
    }
}

void MainWindow::on_pb_tongji_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

    m_tongjiUser.swap(QList<User>());

    for(int i= 0 ; i < m_zhengliUser.size();i++)
    {
       User user = m_zhengliUser.at(i);
       bool bFind = false;
       for(int j= 0 ; j < m_tongjiUser.size();j++)
       {
          User tjUser = m_tongjiUser.at(j);
          if(tjUser.xi_ == user.xi_ && tjUser.name == user.name)
          {
              tjUser.mai_ += user.mai_;
              m_tongjiUser.replace(j,tjUser);
              bFind = true;
              break;
          }
       }
       if(!bFind)
       {
           m_tongjiUser.push_back(user);
       }
    }
    qSort(m_tongjiUser.begin(), m_tongjiUser.end(), ListSortUser);
    ui->tableWidget_jieguo->clearContents();
    ui->tableWidget_jieguo->setRowCount(m_tongjiUser.size());

    ui->textEdit->setText("");
    int numZong = 0;
    for(int j= 0 ; j < m_tongjiUser.size();j++)
    {
        User tjUser = m_tongjiUser.at(j);
        addTableItemJieGuo(QStringLiteral("%1系").arg(tjUser.xi_),j,0);
        addTableItemJieGuo((tjUser.name),j,1);
        addTableItemJieGuo(QString::number(tjUser.mai_),j,2);
        numZong+=tjUser.mai_;
    }
    QString StrTj = QStringLiteral("%1喊麦情况（%2麦）:\n").arg(ui->lineEdit->text()).arg(numZong);
    ui->textEdit->append(StrTj);
    QStringList jieguoList;
    for(int i = 0; i < 9 ;i++)
    {
        int num = 0;
        QString jieguoStr;
        for(int j= 0 ; j < m_tongjiUser.size();j++)
        {
            User tjUser = m_tongjiUser.at(j);
            if(tjUser.xi_ == i+1)
            {
                jieguoStr += QStringLiteral("%1%2 ").arg(tjUser.name).arg(tjUser.mai_);
                num += tjUser.mai_;
            }
        }
        QString Str = QStringLiteral("%1系(%2麦):%3\n").arg(i+1).arg(num).arg(jieguoStr);
        ui->textEdit->append(Str);
    }

}
//截取
void MainWindow::on_pb_jiequ_clicked()
{
    QList<User> zhengliUser;
    for(int i= 0 ; i < m_zhengliUser.size();i++)
    {
       User user = m_zhengliUser.at(i);

       QTableWidgetItem*item  = ui->tableWidget->item(i,1);
       if(item != 0)
       {
		   QString str = user.str;
           int num = item->text().toInt();
           QString strTmp;
           if(str.length() < num)
           {
               strTmp = str;
           }
           else
           {
               strTmp = str.left(num);
           }
		   user.len = num;
           QString strTmp1 = strTmp.left(1);
           if(strTmp1.toInt() > 0)
           {
               user.xi_ = strTmp1.toInt();
               int len = strTmp.length();
               int n=0;

               if(len > 2)
               {
                  QString  c1 = strTmp.mid(len-1,1);
                  QString  c2 = strTmp.at(len-2);
                   n = c2.toInt()*10;
                   n += c1.toInt();

               }
               if(n > 10)
                   user.name = (strTmp.mid(1,len-3));
               else if(n > 0)
                   user.name = (strTmp.mid(1,len-2));
               else
                   user.name = (strTmp.mid(1,len-1));
               if(n == 0)
                   n = 1;
               user.mai_ = n;
           }
           else
           {

           }
       }
       zhengliUser.push_back(user);
    }

    m_zhengliUser.swap(zhengliUser);
    for(int j= 0 ; j < m_zhengliUser.size();j++)
    {
		User tjUser = m_zhengliUser.at(j);
		addTableItem((tjUser.str), j, 0);
		addTableItem(QString::number(tjUser.len), j, 1);
        addTableItem(QStringLiteral("%1系").arg(tjUser.xi_),j,2);
        addTableItem((tjUser.name),j,3);
        addTableItem(QString::number(tjUser.mai_),j,4);
    }
}
