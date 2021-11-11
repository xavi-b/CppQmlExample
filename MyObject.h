#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int myproperty READ getMyProperty WRITE setMyProperty NOTIFY myPropertyChanged)
public:
    int getMyProperty() const
    {
        return myproperty;
    }
    void setMyProperty(int i)
    {
        if(myproperty == i)
            return;

        myproperty = i;
        emit myPropertyChanged();
    }

    Q_INVOKABLE
    void myFunction()
    {
        qDebug() << "MyObject";
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyObject::timerSignal);
        timer->setSingleShot(false);
        timer->start(5000);
    }

signals:
    void myPropertyChanged();
    void timerSignal();

private:
    int myproperty = 0;
};

#endif // MYOBJECT_H
