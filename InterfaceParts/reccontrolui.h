#ifndef RECCONTROLUI_H
#define RECCONTROLUI_H

#include <QWidget>
#include <QDate>
#include <QTime>

namespace Ui {
class RecControlUI;
}

class RecControlUI : public QWidget
{
    Q_OBJECT

public:
    explicit RecControlUI(QWidget *parent = 0);
    ~RecControlUI();

private:
    Ui::RecControlUI *ui;

private:

    void setFileName(const QDate& date = QDate::currentDate(),
                     const QTime& time = QTime::currentTime());

private slots:

    void changeState(bool clicked);

signals:

    void recStatusChanged(bool isRec, const QString& fileName);
};

#endif // RECCONTROLUI_H
