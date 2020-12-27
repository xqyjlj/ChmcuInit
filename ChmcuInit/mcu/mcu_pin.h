#ifndef MCU_PIN_H
#define MCU_PIN_H

#include <QPushButton>

class mcu_pin: public QPushButton
{
public:
    explicit mcu_pin(QWidget* parent = nullptr);
};

#endif // MCU_PIN_H
