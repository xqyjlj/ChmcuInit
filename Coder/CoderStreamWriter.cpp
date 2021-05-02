/**
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 **
 ** 该文件是ChmcuInit项目的一部分。
 ** 版权所有2021 xqyjlj 
 **
 ** 本程序是免费软件:您可以重新发布和/或修改它
 ** 根据GNU通用公共许可证的条款，由自由软件基金会，或第三版许可证，或(随您选择)任何更新版本。
 **
 ** 分发此程序是希望它会有用，但没有任何保证：甚至没有默示的保证特定目的的适销性或适用性。有关更多详细信息，请参见GNU通用公共许可证。 
 **
 ** 您应该已经与这个程序一起收到GNU通用公共许可证的副本。如果不是，请参见<http://www.gnu.org/licenses/>。
 ** 
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-04-29     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "CoderStreamWriter.h"

CoderStreamWriter::CoderStreamWriter(QObject *parent, QIODevice *device) : QObject(parent)
{
    m_streamWriter.setDevice(device);
}

void CoderStreamWriter::writeHeader(const QString &header)
{
    writeTag(u8"ChmcuInit include");
    m_streamWriter << QString("#include \"%1\"\n").arg(header);
    writeEndTag();
}

void CoderStreamWriter::writeComment(const QString &comment)
{
    m_streamWriter << QString(u8"\n/* %1 */\n").arg(comment);
}

void CoderStreamWriter::writeTag(const QString &comment)
{
    m_tag = comment;
    m_streamWriter << QString(u8"\n/*--> %1 Begin */\n").arg(m_tag);
}

void CoderStreamWriter::writeEndTag()
{
    m_streamWriter << QString(u8"/*--> %1 End */\n").arg(m_tag);
    m_tag.clear();
}

void CoderStreamWriter::writeFileHeaderComment(const QString &file, const QString &brief)
{
    m_streamWriter << c_fileHeaderComment.arg(file, brief);
}

void CoderStreamWriter::writeFunction(const CoderStreamWriter::Function_T &function)
{
    QString paramComment;
    if (function.paramComment.isEmpty())
    {
        paramComment = u8"null";
    }

    QString returnComment;
    if (function.paramComment.isEmpty())
    {
        returnComment = R_void;
    }

    m_streamWriter << c_fileFunctionComment.arg(function.briefComment, paramComment, returnComment);

    QString inputs;
    if (function.inputs.isEmpty())
    {
        inputs = R_void;
    }

    QString returnType;
    if (returnType.isEmpty())
    {
        returnType = R_void;
    }

    m_streamWriter << QString(u8"%1 %2(%3)\n").arg(returnType, function.name, inputs);
}

void CoderStreamWriter::writeStartFunction()
{
    m_streamWriter << u8"{\n";
}

void CoderStreamWriter::writeEndFunction()
{
    m_streamWriter << u8"}\n";
}

void CoderStreamWriter::writeElement(const QString &type, const QString &name, const QString &value)
{
    m_streamWriter << QString(u8"%1 %2 = %3;\n").arg(type, name, value);
}

void CoderStreamWriter::writeAttribute(const QString &name, const QString &value)
{
    m_streamWriter << QString(u8"%1 = %2;\n").arg(name, value);
}

void CoderStreamWriter::writeCommand(const QString &name, const QStringList &parameters)
{
    m_streamWriter << QString(u8"%1(%2);\n").arg(name, parameters.join(u8", "));
}

void CoderStreamWriter::writeCommand(const QString &name)
{
    m_streamWriter << QString(u8"%1();\n").arg(name);
}

void CoderStreamWriter::writeLine()
{
    m_streamWriter << "\n";
}


