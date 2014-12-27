#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void equalSum(QList<float> list);
    void newDataFound();

private slots:
    void on_NumEdit_textChanged(const QString &arg1);

    void on_SumEdit_textChanged(const QString &arg1);

    void on_NumListEdit_textChanged(const QString &arg1);

    void equalSumFound(QList<float> list);

    void updateList();
private:
    Ui::Widget *ui;
    float                   m_sum;
    int                     m_cnt;
    QList<QList<float> >     m_list;
};

#endif // WIDGET_H
