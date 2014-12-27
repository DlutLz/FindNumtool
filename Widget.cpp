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
    connect(this, SIGNAL(equalSum(QList<float>)),
            this, SLOT(equalSumFound(QList<float>)));
    connect(this, SIGNAL(newDataFound()), this, SLOT(updateList()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_NumEdit_textChanged(const QString &arg1)
{
    m_cnt = arg1.toUInt();
}

void Widget::on_SumEdit_textChanged(const QString &arg1)
{
    m_sum = arg1.toFloat();
}

void Widget::on_NumListEdit_textChanged(const QString &arg1)
{
    QList<QString> numStrList = arg1.split(",");
    if(numStrList.size() < m_cnt){
        return;
    }
    QList<float> numList;
    foreach (QString numStr, numStrList) {
        numList.append(numStr.toFloat());
    }
    for(int x = 0; x < numList.size() - m_cnt + 1; ++x){
        float *num = new float[m_cnt];
        for(int y = 0; y < m_cnt - 1; ++y){
            num[y] = numList.at(x + y);
        }
        for(int z = m_cnt - 1; z < numList.size(); ++z){
            num[z] = numList.at(z);
            float sum = 0;
            QList<float> list;
            for(int cnt = 0; cnt < m_cnt; ++cnt){
                sum += num[cnt];
                list.append(num[cnt]);
            }
            qDebug() << list;
            if(m_sum == sum){
                emit equalSum(list);
            }
        }
        delete [] num;
    }
}

void Widget::equalSumFound(QList<float> list)
{
    foreach (QList<float> l, m_list) {
        if(l ==list){
            return;
        }
    }
    m_list.append(list);
    emit newDataFound();
}

void Widget::updateList()
{
    ui->numOfLineEdit->clear();
    QString text;
    foreach (QList<float> numList, m_list) {
        QString n;
        foreach (float num, numList) {
            QString str = QString("%1").arg(num);
            n.append(str);
        }
        n.append('\n');
        text.append(n);
    }
    ui->numOfLineEdit->setText(text);
}
