#include "Widget.h"
#include "ui_Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_sum(0.0)
    , m_cnt(0)
    , m_list()
{
    ui->setupUi(this);
    connect(this, SIGNAL(equalSum()),this, SLOT(equalSumFound()));
    connect(this, SIGNAL(newDataFound()), this, SLOT(updateList()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_NumEdit_textChanged(const QString &arg1)
{
    m_cnt = arg1.toUInt();
    m_list.clear();
    QString str = ui->NumListEdit->text();
    on_NumListEdit_textChanged(str);
}

void Widget::on_SumEdit_textChanged(const QString &arg1)
{
    m_sum = arg1.toFloat();
    m_list.clear();
    QString str = ui->NumListEdit->text();
    on_NumListEdit_textChanged(str);
}

void Widget::on_NumListEdit_textChanged(const QString &arg1)
{
    m_list.clear();
    ui->numOfLineEdit->setText("");
    QList<QString> numStrList = arg1.split(",");
    findEqualNum(numStrList);

    if(numStrList.size() < m_cnt || m_cnt == 0){
        return;
    }

    QList<float> numList;
    foreach (QString numStr, numStrList) {
        float a = numStr.toFloat();
        numList.append(a);
    }
    for(int x = 0; x < numList.size() - m_cnt + 1; ++x){
        float *num = new float[m_cnt];
        for(int y = 0; y < m_cnt - 1; ++y){
            num[y] = numList.at(x + y);
        }
        for(int z = x + m_cnt - 1; z < numList.size(); ++z){
            num[m_cnt -1] = numList.at(z);
            float sum = 0;
            QList<float> list;
            for(int cnt = 0; cnt < m_cnt; ++cnt){
                sum += num[cnt];
                list.append(num[cnt]);
            }
            float diff = m_sum - sum;
            if((diff + (float)0.001 >0) && (diff - (float)0.001 < 0)){
                m_list.append(list);
                emit equalSum();
            }
        }
        delete [] num;
    }
}

void Widget::equalSumFound()
{
    emit newDataFound();
}

void Widget::updateList()
{
    ui->numOfLineEdit->setText("");
    QString text;
    foreach (QList<float> numList, m_list) {
        QString n;
        foreach (float num, numList) {
            QString str = QString("%1 ").arg(num);
            n.append(str);
        }
        text.append(n);
        text.append("; ");
    }
    ui->numOfLineEdit->setText(text);
}

void Widget::findEqualNum(QList<QString> strList)
{
    ui->equalNumlineEdit->setText("");
    if(strList.size() < 2){
        return;
    }
    QList<float> numList;
    foreach (QString numStr, strList) {
        numList.append(numStr.toFloat());
    }
    QList<float> findList;

    for(int x = 0; x < numList.size(); ++x){
        bool flag = false;
        foreach(float f, findList){
            if(f == numList.at(x)){
                flag = true;
                continue;
            }

        }

        if(flag){
            continue;
        }
        int cnt = 1;
        for(int y = x + 1; y < numList.size(); ++y){
            if(numList.at(x) == numList.at(y)){
                cnt++;
            }
        }
        if(cnt > 1){
            findList.append(numList.at(x));
            updateEqualNumList(numList.at(x), cnt);
        }
    }
}

void Widget::updateEqualNumList(float equalNum, int cnt)
{
    QString str = QString("num:%1 (%2);").arg(equalNum).arg(cnt);
    QString tmp = ui->equalNumlineEdit->text().append(str);
    ui->equalNumlineEdit->setText(tmp);
}
