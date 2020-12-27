#include "mcu_chip.h"

mcu_chip::mcu_chip(QWidget* parent): QLabel(parent)
{
    QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy1);
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QSize(16777215, 16777215));
    this->setSizeIncrement(QSize(44, 78));
    this->setBaseSize(QSize(44, 78));
    this->setAutoFillBackground(false);
    this->setScaledContents(true);
}
