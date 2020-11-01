#ifndef BINSPARAMUI_H
#define BINSPARAMUI_H

#include <QWidget>
#include <QScopedPointer>

#include "./defaultradiobtngroup.h"
#include "./labelwithlineedit.h"

namespace Ui {
class BINSParamUI;
}

/*!
 * \brief BINSParamUI - класс для отображения Параметров работы с БИНС
 * \details В него входит несколько компонентов:
 *          1. DefaultRadioBtnGroup
 *          2. LabelWithLineEdit
 *          Если смотреть на форму через дизайнер, то на ней отображено не все.
 *          Компоненты, описанные выше, я добавлял вручную (см. .срр)
 */

class BINSParamUI : public QWidget
{
    Q_OBJECT

public:
    explicit BINSParamUI(QWidget *parent = 0);
    ~BINSParamUI();

    void fillInputFromFile(const QPair<QString, QString>& inputText);

private:
    Ui::BINSParamUI *ui;

    QScopedPointer<LabelWithLineEdit>   m_LatInput;
    QScopedPointer<LabelWithLineEdit>   m_LonInput;
    QScopedPointer<DefaultRadioBtnGroup>    m_radioHow;
    QScopedPointer<DefaultRadioBtnGroup>    m_radioWho;

private:

    void configUI();    // Накидываем компоненты на виджет
    void setUIState();  // Устанавливаем начальное состояние кнопок и прочего

    void clearInput();

signals:

    // Отвечает за то, в каком состоянии находится БИНС:
    // Ввод или Автономность
    void changeOperatorInputMethod();

    // id = 0 - оператор
    // id = 1 - СНС
    void changeCoordinateSource(size_t id);

    void applyChanges(QPair<float, float> inputData);

    void resetBINS();

private slots:

    void setSubFormState(size_t id);

    void setInputState(size_t id); // Блокируем инпуты, или делаем доступными


};

#endif // BINSPARAMUI_H
