#ifndef MCU_PIN_H
#define MCU_PIN_H

#include <QComboBox>

class mcu_pin: public QComboBox
{
    Q_OBJECT
public:
    explicit mcu_pin(QWidget* parent = nullptr);
    void setconnect(void);
Q_SIGNALS:
    void sigPopup();
protected:
    void showPopup();
private slots:
    void textchanged(int index);
private:

};

#endif // MCU_PIN_H
