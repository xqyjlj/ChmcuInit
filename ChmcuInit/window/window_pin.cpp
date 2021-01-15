#include "window_pin.h"
#include "QDebug"
#include <QTreeWidgetItem>
window_pin::window_pin(QWidget* parent, QString path) : QTreeWidget(parent)
{
    xml_file_path = path;
    fun_mcu_xml = new mcu_xml(this);

    for (int i = 1; i <= 24; i++)
    {
        QStringList list;
        list = fun_mcu_xml->read_pin(":/mcu/hc32/res/db/mcu/HDSC/HC32/HC32F002/HC32F002D4P8.xml", list, i);
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << QString::number(i) + QString(" : ") + list.at(0));
        item->setWhatsThis(0, QString::number(i));
        for (int i = 0; i < list.length() - 1; i++)
        {
            QTreeWidgetItem* it_item = new QTreeWidgetItem(QStringList() << list.at(i + 1));
            it_item->setWhatsThis(0, QString::number(i + 1));
            item->addChild(it_item);
        }
        this->addTopLevelItem(item);
    }
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(item_double_clicked(QTreeWidgetItem*, int)), Qt::UniqueConnection);
}

void window_pin::item_double_clicked(QTreeWidgetItem* item, int column)
{
    if(item->parent())
    {
        bool isischange = (item->backgroundColor(0) == Qt::green);
        emit item_doubled_clicked_info(item->parent()->whatsThis(column).toInt(), item->whatsThis(column).toInt(), isischange);
        qDebug() << item->parent()->whatsThis(column).toInt() << item->whatsThis(column).toInt();
    }
}

void window_pin::change_item_color(int pin, int function, bool ischange)
{
    qDebug() << pin << function << ischange;
    QTreeWidgetItem* item = this->topLevelItem(pin - 1);
    if(item)
    {
        qDebug() << item->whatsThis(0);
        QTreeWidgetItem* it_item = item->child(function - 1);
        if(it_item)
        {
            qDebug() << it_item->whatsThis(0);
            if(ischange)
            {
                it_item->setBackgroundColor(0, Qt::green);
            }
            else
            {
                it_item->setBackgroundColor(0, QColor(Qt::white));
            }
        }
    }
}

void window_pin::set_xml_file_path(QString path)
{
    xml_file_path = path;
}
