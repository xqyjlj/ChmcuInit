#ifndef MCU_TSSOP24_H
#define MCU_TSSOP24_H

#include <QObject>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

#include "mcu_xml.h"
#include "mcu_pin.h"
#include <QList>
#include "mcu_chip.h"
class mcu_tssop24: public QGroupBox
{
public:
    explicit mcu_tssop24(QWidget* parent = nullptr);

public:
    void set_pin();
protected:

private:
    void set_pin_menu(mcu_pin* pin, QStringList list);
private:
    QGridLayout* gridLayout = new QGridLayout(this);
    mcu_chip* chip = new mcu_chip();

    mcu_pin* pin1 = new mcu_pin(this);
    mcu_pin* pin2 = new mcu_pin(this);
    mcu_pin* pin3 = new mcu_pin(this);
    mcu_pin* pin4 = new mcu_pin(this);
    mcu_pin* pin5 = new mcu_pin(this);
    mcu_pin* pin6 = new mcu_pin(this);
    mcu_pin* pin7 = new mcu_pin(this);
    mcu_pin* pin8 = new mcu_pin(this);
    mcu_pin* pin9 = new mcu_pin(this);
    mcu_pin* pin10 = new mcu_pin(this);
    mcu_pin* pin11 = new mcu_pin(this);
    mcu_pin* pin12 = new mcu_pin(this);
    mcu_pin* pin13 = new mcu_pin(this);
    mcu_pin* pin14 = new mcu_pin(this);
    mcu_pin* pin15 = new mcu_pin(this);
    mcu_pin* pin16 = new mcu_pin(this);
    mcu_pin* pin17 = new mcu_pin(this);
    mcu_pin* pin18 = new mcu_pin(this);
    mcu_pin* pin19 = new mcu_pin(this);
    mcu_pin* pin20 = new mcu_pin(this);
    mcu_pin* pin21 = new mcu_pin(this);
    mcu_pin* pin22 = new mcu_pin(this);
    mcu_pin* pin23 = new mcu_pin(this);
    mcu_pin* pin24 = new mcu_pin(this);

    mcu_xml* fun_mcu_xml = new mcu_xml(this);

    QList<mcu_pin*> pin_list = QList<mcu_pin*>() << pin1 << pin2 << pin3 << pin4 << pin5 << pin6 << pin7 << pin8 << pin9
                               << pin10 << pin11 << pin12 << pin13 << pin14 << pin15 << pin16 << pin17
                               << pin18 << pin19 << pin20 << pin21 << pin22 << pin23 << pin24;
};

#endif // MCU_TSSOP24_H
